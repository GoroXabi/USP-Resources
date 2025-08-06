#include "utils.hpp"
#include "csv.hpp"

///////////////////////////////////
//
//  Clase Student
//
///////////////////////////////////

//Función constructora que inicializa un estudiante sin preferencias
Student::Student()
    : pref_cluster(0), pref_row(0), pref_seat(0), other_id_1(0), other_id_2(0) {}

//Función constructora que inicializa un estudiante con las preferencias indicadas
Student::Student(int pref_c, int pref_r, int pref_s, int o_id1, int o_id2)
    : pref_cluster(pref_c), pref_row(pref_r), pref_seat(pref_s), other_id_1(o_id1), other_id_2(o_id2) {}

//Función que devuelve el cluster, fila y asiento deseado (positivo) / no deseado (negativo)
void    Student::get_seat_preference(int *cluster, int *row, int *seat){
    *cluster = this->pref_cluster;
    *row = this->pref_row;
    *seat = this->pref_seat;
}

//Función que devuelve los IDs de los estudiantes que se quieren tener cerca (positivo) / lejos (negativo)
void    Student::get_student_preference(int *id1, int *id2){
    *id1 = this->other_id_1;
    *id2 = this->other_id_2;
}

///////////////////////////////////
//
//  Clase Location
//
///////////////////////////////////

//Función constructora que inicializa una localización seleccionada vacía
Location::Location()
    : final_cluster(0), final_row(0), final_seat(0) {}

//Función que devuelve la localización seleccionada
void    Location::get_seat(int *cluster, int *row, int *seat){
    *cluster = this->final_cluster;
    *row = this->final_row;
    *seat = this->final_seat;
}

//Función que establece la localización seleccionada
int    Location::sit_down(int cluster, int row, int seat){
    if(cluster < 1 || cluster > N_CLUSTERS || row < 1 || row > N_ROWS || seat < 1 || seat > N_SEATS){
        std::cerr << "El localización indicado no existe." << std::endl;
        return(1);
    }
    this->final_cluster = cluster;
    this->final_row = row;
    this->final_seat = seat;
    return(0);
}

///////////////////////////////////
//
//  Clase USP
//
///////////////////////////////////

//Función constructora que inicializa el problema a resolver
USP::USP(int n_c, int n_r, int n_s, std::string instance_path)
    : n_students(n_c*n_r*n_s), n_clusters(n_c), n_rows(n_r), n_seats(n_s)  {

        //Leer la instancia del problema
        io::CSVReader<6> in(instance_path);
        in.read_header(io::ignore_extra_column, "ID", "Cluster", "Row", "Seat", "Other_ID_1", "Other_ID_2");

        int id, c, r, s, o_id1, o_id2;
        while(in.read_row(id, c, r, s, o_id1, o_id2)){
            //Añadir estudiante con las preferencias indicadas a la instancia
            Student student(c,r,s,o_id1,o_id2);
            this->instance[id] = student;
            //Inicializar la localización seleccionada para el estudiante como vacía (0,0,0)
            Location answer;
            this->solution[id] = answer;
        }
    }


//Función que devuelve la cantidad de clusters, filas y asientos en el problema
void    USP::get_dimensions(int *n_clusters, int *n_rows, int *n_seats){
    *n_clusters = this->n_clusters;
    *n_rows = this->n_rows;
    *n_seats = this->n_seats;
}

//Función que devuelve la cantidad de estudiantes en el problema
int    USP::get_size(){
    return(this->n_students);
}

//Función que devuelve el cluster, fila y asiento deseado (positivo) / no deseado (negativo) por el estudiante con el ID indicado
int     USP::get_seat_preference(int id, int *pref_cluster, int *pref_row, int *pref_seat){
    if(this->instance.find(id) == this->instance.end()){
        std::cerr << "El estudiante indicado no existe." << std::endl;
        return 1;
    }
    this->instance[id].get_seat_preference(pref_cluster,pref_row,pref_seat);
    return(0);
}

//Función que devuelve los IDs de los estudiantes que quiere tener cerca (positivo) / lejos (negativo) el estudiante con el ID indicado
int     USP::get_student_preference(int id, int *other_id_1, int *other_id_2){
    if(this->instance.find(id) == this->instance.end()){
        std::cerr << "El estudiante indicado no existe." << std::endl;
        return 1;
    }
    this->instance[id].get_student_preference(other_id_1,other_id_2);
    return(0);
}

//Función que "sienta" a un estudiante en la localización (cluster,fila,asiento)
int    USP::sit_down(int id, int cluster, int row, int seat){
    if(this->solution.find(id) == this->solution.end()){
        std::cerr << "El estudiante indicado no existe." << std::endl;
        return 1;
    }
    this->solution[id].sit_down(cluster,row,seat);
    return(0);
}

//Función que devuelve el cluster, fila y asiento donde se encuentra el estudiante con el ID indicado
//En caso de que aún no se haya sentado al estudiante, devuelve (0,0,0)
int    USP::get_seat(int id, int *cluster, int *row, int *seat){
    if(this->solution.find(id) == this->solution.end()){
        std::cerr << "El estudiante indicado no existe." << std::endl;
        return 1;
    }
    this->solution[id].get_seat(cluster,row,seat);
    return(0);
}

//Función que evalua la solución actual
int   USP::evaluate()
{
    std::unordered_set<std::string> seen;
    int pref_c , pref_r , pref_s , other_id_1 , other_id_2 , other_c_1 , other_r_1 , other_s_1 , other_c_2 , other_r_2 , other_s_2 ,
    distance_1, distance_2, final_c , final_r , final_s , total_points;

    total_points = 0;

    //Para cada estudiante en las solución...
    for (auto& pair : solution) {
        auto& key = pair.first;
        auto& value = pair.second;
        
        this->instance[key].get_seat_preference(&pref_c,&pref_r,&pref_s);
        value.get_seat(&final_c,&final_r,&final_s);

        //Validar que la localización exista
        if((final_c) < 1 || (final_c) > (this->n_clusters) || (final_r) < 1 || (final_r) > (this->n_rows) || (final_s) < 1 || (final_s) > (this->n_seats)){
            std::cerr << "Localización no válida para el estudiante " << key << "." << std::endl;
            return -1;
        }

        //Validar que no haya localizaciones duplicadas
        std::stringstream ss;
        ss << final_c << " " << final_r << " " << final_s;
        if (seen.count(ss.str())) {
            std::cerr << "Localizaciones repetidas en la solución." << std::endl;
            return -1;
        }
        seen.insert(ss.str());

        //Preferencias de cluster, fila y asiento
		if (((pref_c) > 0 && (final_c) == (pref_c)) || ((pref_c) < 0 && (final_c) != (-pref_c)))
			total_points++;
		if (((pref_r) > 0 && (final_r) == (pref_r)) || ((pref_r) < 0 && (final_r) != (-pref_r)))
			total_points++;
		if (((pref_s) > 0 && (final_s) == (pref_s)) || ((pref_s) < 0 && (final_s) != (-pref_s)))
			total_points++;
		
        this->instance[key].get_student_preference(&other_id_1,&other_id_2);

        //Preferencia con respecto a otros estudiante
		this->solution[std::abs(other_id_1)].get_seat(&other_c_1,&other_r_1,&other_s_1);
		this->solution[std::abs(other_id_2)].get_seat(&other_c_2,&other_r_2,&other_s_2);

        //Calcular distancia de manhattan entre estudiantes (si están en un cluster distinto, se consideran a distancia máxima)
        if ((final_c) != (other_c_1)) distance_1 = MAX_RADIO;
        else distance_1 = abs((final_r) - (other_r_1)) + abs((final_s) - (other_s_1));
        if ((final_c) != (other_c_2)) distance_2 = MAX_RADIO;
        else distance_2 = abs((final_r) - (other_r_2)) + abs((final_s) - (other_s_2));
        
        //La puntuación se calcula de forma proporcional a la distancia con respecto a los otros estudiantes
        //Se limita la mayor puntuación posible a MAX_RADIO-1
        if ((other_id_1) > 0)
            total_points += (MAX_RADIO - std::min(distance_1, MAX_RADIO));
        else
            total_points += (std::min(distance_1, MAX_RADIO) - 1);

        if ((other_id_2) > 0)
            total_points += (MAX_RADIO - std::min(distance_2, MAX_RADIO));
        else
            total_points += (std::min(distance_2, MAX_RADIO) - 1);

	}
	return (total_points);
}

//Printea la solución en formato csv
int    USP::print_solution(std::string solution_path){
    
    int c, r, s;

    std::ofstream file(solution_path);

    if (!file) {
        std::cerr << "No se pudo escribir la solución." << std::endl;
        return 1;
    }

    file << "ID,Location" << std::endl;

    for (auto& pair : this->solution) {
        pair.second.get_seat(&c,&r,&s);
        file << pair.first << ",c" << c << "r" << r << "s" << s << std::endl;
    }

    file.close();

    return 0;
}