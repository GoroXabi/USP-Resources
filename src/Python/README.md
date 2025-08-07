# USP CÓDIGO BASE - VERSION PYTHON 🐍

> 📝 **Requisitos:** Es necesario disponer de la librería *pandas* (>=2.2.3).

Esta carpeta incluye el código base para la implementación de vuestras soluciones en Python. Todas las funcionalidades básicas necesarias están incluidas en la clase USP definida en el fichero *utils.py*. **NO ES NECESARIO MODIFICAR DICHO FICHERO**, podéis implementar vuestra solución directamente en el fichero *optimizer.py*, tal como se os indica. Para ello, hay varias funciones de la clase USP que necesitaréis utilizar:

 - **get_dimensions():** Función que devuelve la cantidad de clusters, filas y asientos en el problema.

 - **get_size():** Función que devuelve la cantidad de estudiantes (y, por lo tanto, localizaciones) en el problema.

  - **get_seat_preference(int id)**: Función que devuelve las preferencias de cluster, fila y asiento del estudiante con el ID indicado. Un valor positivo implica que le estudiante quiere estar en ese cluster/fila/asiento, mientras que un valor negativo indica que no quiere estar en ese cluster/fila/asiento.

  - **get_student_preference(int id)**: Función que devuelve los IDs de les estudiantes con respecto a los cuales tiene una preferencia relacional le estudiante con el ID indicado. Un valor positivo implica una preferencia de cercanía, mientras que un valor negativo indica una preferencia de lejanía.

 - **get_seat(student_id):** Función que devuelve la localización del estudiante con el ID indicado. En caso de que le estudiante aún no tenga ninguna localización asignada, devolverá (0,0,0).

 - **sit_down(student_id,cluster,row,seat):** Función que sienta al estudiante con el ID indicado en la localización definida por las variables cluster, row y seat.

 - **evaluate():** Función que devuelve la puntuación total de la solución actual. Cuanto mayor sea el valor retornado, mejor será la solución.

 - **print_solution(solution_path):** Función que imprime la solución en el fichero indicado con el formato correcto para ser procesado por el juez online.

El fichero *main.py* incluye una función de ejemplo que genera una solución aleatoria al problema para que podáis observar el funcionamiento básico de la interfaz proporcionada.

> ⚠️ **Warning:** El rango de IDs de estudiante válidos es **1-192**. Los rangos de clusters, filas y asientos válidos son **1-4**, **1-8** y **1-6**, respectivamente. Valores fuera de estos rangos darán error, ya que se estaría accediendo a estudiantes/localizaciones que no existen.
