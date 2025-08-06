# URDULIZ SEATING PROBLEM (USP)

Esta carpeta incluye el código base para la implementación de la solución al USP en Python. Todas las funcionalidades básicas necesarias están incluidas en la clase USP definida en el fichero "utils.py". NO ES NECESARIO MODIFICAR DICHO FICHERO, podéis implementar vuestra solución directamente en el fichero "optimizer.py", tal como se os indica. Para ello, hay varias funciones de la clase USP que necesitaréis utilizar:

 - get_dimensions(): Función que devuelve la cantidad de clusters, filas y asientos en el problema.

 - get_size(): Función que devuelve la cantidad de estudiantes (y, por lo tanto, localizaciones) en el problema.

 - get_seat(student_id): Función que devuelve la localización del estudiante con el ID indicado. En caso de que el estudiante aún no tenga ningún asiento asignado, devolverá (0,0,0).

 - sit_down(student_id,cluster,row,seat): Función que sienta al estudiante con el ID indicado en la localización definida por las variables cluster, row y seat.

 - evaluate(): Función que devuelve la calidad de la solución actual. Cuanto mayor sea el valor retornado, mejor será la solución.

 - print_solution(solution_path): Función que imprime la solución en el fichero indicado con el formato correcto para ser procesado por el juez online.

El fichero "main.py" incluye una función de ejemplo que genera una solución aleatoria al problema para que podáis observar el funcionamiento básico de la interfaz proporcionada.

REQUISITOS: Es necesario instalar la librería "pandas(>=2.2.3)" para el correcto funcionamiento de las utilidades proporcionadas.
