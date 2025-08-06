import pandas as pd
import random

#Paths de los ficheros de instancia (students.csv) y solución actual (solution.csv)
PATH_INSTANCE = "../../data/students.csv"
PATH_SOLUTION = "../../data/solution.csv"

#Dimensiones del problema (la cantidad de estudiantes será N_CLUSTERS*N_ROWS*N_SEATS)
N_CLUSTERS = 4
N_ROWS = 8
N_SEATS = 6

#Máximo radio a considerar en las preferencias con respecto a otros estudiantes
MAX_RADIO = 4

###################################
##
##  Clase USP
##
###################################

class USP():

    #Función constructora que inicializa el problema a resolver
    def __init__(self,n_clusters,n_rows,n_seats,instance_path):

        #Número de estudiantes
        self.__n_students = n_clusters*n_rows*n_seats
        #Número de clusters
        self.__n_clusters = n_clusters
        #Número de filas
        self.__n_rows = n_rows
        #Número de asientos por fila
        self.__n_seats = n_seats

        #Leemos el fichero de instancia para guardarlo como un Dataframe
        try:
            self.__instance = pd.read_csv(instance_path)
            self.__instance["ID"] = pd.to_numeric(self.__instance["ID"],downcast="integer")
            self.__instance = self.__instance.set_index("ID")
        except:
            raise ValueError(f"No se ha podido leer la instancia, formato incorrecto.")
        
        if len(self.__instance.index) != self.__n_students:
            raise ValueError(f"Las dimensiones indicadas no concuerdan con la cantidad de alumnos en la instancia.")

        #Inicializamos una solución vacía
        self.__solution = pd.DataFrame({"ID":[i for i in range(1,self.__n_students+1)],"Location": ["c0r0s0" for _ in range(1,self.__n_students+1)]})
        self.__solution["ID"] = pd.to_numeric(self.__solution["ID"],downcast="integer")
        self.__solution = self.__solution.set_index("ID")
    
    #Función que "sienta" a un estudiante en la localización (cluster,fila,asiento)
    def sit_down(self,student_id,cluster,row,seat):
        if(student_id not in self.__solution.index):
            raise ValueError("El estudiante indicado no existe.")
        if(not (1 <= cluster <= N_CLUSTERS and 1 <= row <= N_ROWS and 1 <= seat <= N_SEATS)):
            raise ValueError("La localización indicada no existe.")
        self.__solution.loc[student_id,"Location"] = "c"+str(cluster)+"r"+str(row)+"s"+str(seat)

    #Función que devuelve el cluster, fila y asiento donde se encuentra el estudiante con el ID indicado
    #En caso de que aún no se haya sentado al estudiante, devuelve (0,0,0)
    def get_seat(self,student_id):
        if(student_id not in self.__solution.index):
            raise ValueError("El estudiante indicado no existe.")
        c, rest = self.__solution.loc[student_id,"Location"].split('r', 1)
        r, s = rest.split('s', 1)
        return int(c[1:]), int(r), int(s)
    
    #Función que devuelve la solución actual
    def get_solution(self):
        return(self.__solution)

    #Función que devuelve la instancia del problema
    def get_instance(self):
        return(self.__instance)
    
    #Función que devuelve la cantidad de clusters, filas y asientos en el problema
    def get_dimensions(self):
        return(self.__n_clusters,self.__n_rows,self.__n_seats)
    
    #Función que devuelve la cantidad de estudiantes en el problema
    def get_students(self):
        return(self.__n_students)
    
    #Función que evalua la solución actual
    def evaluate(self):

        #Validar que no haya localizaciones duplicadas
        if self.__solution["Location"].duplicated().any():
            raise ValueError("Localizaciones repetidas en la solución.")

        #Accesos rápidos
        values = self.__instance.to_numpy()
        student_ids = self.__instance.index.to_numpy()

        #Hallar localizaciones de todos los estudiantes y guardarlos en cache
        seats = self.__solution["Location"].str.extract(r'c(?P<c>\d+)r(?P<r>\d+)s(?P<s>\d+)').astype(int)
        seat_cache = dict(zip(self.__solution.index, zip(seats["c"], seats["r"], seats["s"])))

        #Para cada estudiante en las solución...
        total_points = 0
        for i in range(self.__n_students):
            sid = student_ids[i]
            pc, pr, ps, other_id_1, other_id_2 = values[i]
            c, r, s = seat_cache[sid]

            #Validación de las localizaciones
            if not (1 <= c <= self.__n_clusters and 1 <= r <= self.__n_rows and 1 <= s <= self.__n_seats):
                raise ValueError(f"Localización no válida para el estudiante {sid}.")

            #Preferencias de cluster, fila y asiento
            points = int((pc > 0 and c == pc) or (pc < 0 and c != -pc)) + \
                    int((pr > 0 and r == pr) or (pr < 0 and r != -pr)) + \
                    int((ps > 0 and s == ps) or (ps < 0 and s != -ps))

            #Preferencia con respecto a otros estudiantes
            c_o1, r_o1, s_o1 = seat_cache[abs(other_id_1)]
            c_o2, r_o2, s_o2 = seat_cache[abs(other_id_2)]
                
            #Calcular distancia de manhattan entre estudiantes (si están en un cluster distinto, se consideran a distancia máxima)
            dist1 = (abs(r - r_o1) + abs(s - s_o1)) if c == c_o1 else MAX_RADIO
            dist2 = (abs(r - r_o2) + abs(s - s_o2)) if c == c_o2 else MAX_RADIO

            #La puntuación se calcula de forma proporcional a la distancia con respecto a los otros estudiantes
            #Se limita la mayor puntuación posible a MAX_RADIO-1
            points += (MAX_RADIO - min(dist1, MAX_RADIO))*int(other_id_1>0) + \
                    (min(dist1, MAX_RADIO) - 1)*int(other_id_1<0) + \
                    (MAX_RADIO - min(dist2, MAX_RADIO))*int(other_id_2>0) + \
                    (min(dist2, MAX_RADIO) - 1)*int(other_id_2<0)

            total_points += points
        
        return total_points

    #Printea la solución en formato csv
    def print_solution(self,solution_path):
        try:
            self.__solution.to_csv(solution_path,index=True)
        except:
            raise ValueError("No se pudo abrir el archivo indicado.")