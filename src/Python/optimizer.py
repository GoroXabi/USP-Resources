from utils import *

########################################################################
#
#   Función de ejemplo que genera una solución válida aleatoria
#
########################################################################
def random_solution(usp_ins):
    _, n_rows, n_seats = usp_ins.get_dimensions()
    n_students = usp_ins.get_students()

    #Generar una permutación aleatoria de las localizaciones disponibles
    permutation = [i for i in range(n_students)]
    random.shuffle(permutation)
    
    n_seats_rows = n_rows*n_seats

    #Sentar a los estudiantes en el orden indicado por la permutación aleatoria
    for i in range(1,n_students+1):
        usp_ins.sit_down(i,permutation[i-1]//n_seats_rows+1,
                         (permutation[i-1]%n_seats_rows)//n_seats+1,
                         (permutation[i-1]%n_seats_rows)%n_seats+1)

########################################################################
#
#   Bloque principal
#
########################################################################
if __name__ == "__main__":
    
    #Inicializar el objeto que contiene los datos de la instancia
    usp_ins = USP(N_CLUSTERS,N_ROWS,N_SEATS,PATH_INSTANCE)

    #Generar una solución aleatoria para el problema
    random_solution(usp_ins)

    #TODO: AÑADID AQUÍ VUESTRO CÓDIGO:
    # ...
    # ...
    # ...
    # ...

    #Guardar la solución en formato csv
    usp_ins.print_solution(PATH_SOLUTION)

    #Calcular el valor de función objetivo de la solución generada
    print("El fitness de la solución es: " + str(usp_ins.evaluate()))