# USP CÓDIGO BASE - VERSIÓN C++ 💻

Esta carpeta incluye el código base para la implementación de vuestras soluciones en **C++**. Todas las funcionalidades básicas necesarias están incluidas en la clase USP definida en los ficheros *utils.hpp* y *utils.cpp*. **NO ES NECESARIO MODIFICAR DICHOS FICHEROS**, podéis implementar vuestra solución directamente en el fichero *main.cpp*, tal como se os indica. Para ello, hay varias funciones de la clase USP que necesitaréis utilizar:

 - **get_dimensions(int *n_clusters, int *n_rows, int *n_seats)**: Función que guarda en las variables *n_clusters*, *n_rows* y *n_seats* la cantidad de clusters, filas y asientos en el problema, respectivamente.

 - **get_size()**: Función que devuelve la cantidad de estudiantes (y, por lo tanto, localizaciones) en el problema.

 - **get_seat_preference(int id, int *pref_cluster, int *pref_row, int *pref_seat)**: Función que guarda en las variables *pref_cluster*, *pref_row* y *pref_seat* las preferencias de cluster, fila y asiento del estudiante con el ID indicado. Un valor positivo implica que le estudiante quiere estar en ese cluster/fila/asiento, mientras que un valor negativo indica que no quiere estar en ese cluster/fila/asiento.

  - **get_student_preference(int id, int *other_id_1, int *other_id_2)**: Función que guarda en las variables *other_id_1* y *other_id_2* los IDs de les estudiantes con respecto a los cuales tiene una preferencia relacional le estudiante con el ID indicado. Un valor positivo implica una preferencia de cercanía, mientras que un valor negativo indica una preferencia de lejanía.

 - **get_seat(int id, int *cluster, int *row, int *seat)**: Función que guarda en las variables *cluster*, *row* y *seat* la localización del estudiante con el ID indicado. En caso de que le estudiante aún no tenga ninguna localización asignada, devolverá 0 en los tres casos.

 - **sit_down(int id, int cluster, int row, int seat)**: Función que sienta al estudiante con el ID indicado en la localización definida por las variables *cluster*, *row* y *seat*.

 - **evaluate():** Función que devuelve la puntuación total de la solución actual. Cuanto mayor sea el valor retornado, mejor será la solución.

 - **print_solution(std::string solution_path):** Función que imprime la solución en el fichero indicado con el formato correcto para ser procesado por el juez online.

El fichero *main.cpp* incluye una función de ejemplo que genera una solución aleatoria al problema para que podáis observar el funcionamiento básico de la interfaz proporcionada.


> ⚠️ **Warning:** El rango de IDs de estudiante válidos es **1-192**. Los rangos de clusters, filas y asientos válidos son **1-4**, **1-8** y **1-6**, respectivamente. Valores fuera de estos rangos darán error, ya que se estaría accediendo a estudiantes/localizaciones que no existen.
