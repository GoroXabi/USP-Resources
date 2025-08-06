#include "utils.hpp"

//////////////////////////////////////////////////////////////////
//
//  Función de ejemplo que genera una solución válida aleatoria
//
//////////////////////////////////////////////////////////////////
void random_solution(USP *usp_ins){

    int n_clusters, n_rows, n_seats, n_students, n_seats_rows;
    usp_ins->get_dimensions(&n_clusters,&n_rows,&n_seats);
    n_students = usp_ins->get_size();

    //Generar una lista con tantos elemetos como localizaciones
    std::vector<int> permutation(n_students);
    for (int i = 0; i < n_students; ++i)
        permutation[i] = i;

    //Mezclar la lista de localizaciones
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(permutation.begin(), permutation.end(), gen);

    n_seats_rows = (n_rows) * (n_seats);

    //Sentar a los estudiantes en el orden indicado por la permutación aleatoria de localizaciones
    for (int i = 1; i <= n_students; i++) {
        usp_ins->sit_down(i,permutation[i-1]/n_seats_rows+1,
                         (permutation[i-1]%n_seats_rows)/(n_seats)+1,
                         (permutation[i-1]%n_seats_rows)%(n_seats)+1);
    }
}

//////////////////////////////////////////////////////////////////
//
//  Función principal
//
//////////////////////////////////////////////////////////////////
int main()
{
    //Inicializar el objeto que contiene los datos de la instancia
    USP usp_ins(N_CLUSTERS,N_ROWS,N_SEATS,PATH_INSTANCE);

    //Generar una solución aleatoria para el problema
    random_solution(&usp_ins);

    //TODO: AÑADID AQUÍ VUESTRO CÓDIGO:
    // ...
    // ...
    // ...
    // ...

    //Guardar la solución en formato csv
    usp_ins.print_solution(PATH_SOLUTION);

    //Calcular el valor de función objetivo de la solución generada
    std::cout << "El fitness de la solución es: " << usp_ins.evaluate() << std::endl;

    return 0;
}
