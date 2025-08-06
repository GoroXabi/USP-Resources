# URDULIZ SEATING PROBLEM (USP) 🪑

Repositorio desarrollado para el reto Urduliz Seating Problem (USP).

## Contenido 📁

- **data:** Carpeta que contiene la instancia a resolver en formato csv (*students.csv*).
- **src:** Carpeta que contiene el código base (tanto en *C++* como *Python*) para la resolución del problema.

## Descripción del problema ⚙️

Ha terminado agosto y todos los estudiantes de *Urduliz 42* vuelven al campus con todos los clusters abiertos. Los **192** estudiantes se presentan en el lobby para acudir a sus asientos favoritos. Sin embargo, no todo es tan sencillo, ya que las preferencias de los estudiantes en cuanto a dónde sentarse parecen chocar entre sí. Para contentar a todo el mundo, tu trabajo como nuevo acomodador de *Urduliz 42* es decidir dónde se colocará cada estudiante 💺 Tienes 2 horas para hacerlo, o comenzarán las trifulcas…

Varys lo hubiese hecho en lo que tarda en subir el ascensor, pero está en unas merecidas vacaciones… 🏖️🍹

## Objetivo 🎯

Nuestro objetivo es sentar a **TODOS** los estudiantes de *Urduliz 42* en los asientos disponibles a la vez que maximizamos la cantidad de **PUNTOS** 🌠 obtenidos por cumplir las preferencias de los estudiantes. Existen dos tipos de preferencias: *posicionales* y *relacionales*. Cada estudiante podrá aportar un máximo de **9 PUNTOS** 🌠 en caso de que todas sus preferencias se vean satisfechas.

### Preferencias posicionales

Los estudiantes tienen unas preferencias muy marcadas sobre donde quieren (o no quieren) sentarse. En concreto, cada estudiante tiene:

- Un cluster favorito (o no deseado).
- Una fila favorita (o no deseada).
- Un asiento favorito (o no deseado).

Cada preferencia posicional cumplida en cada estudiante sumará **1 PUNTO** 🌠 a la puntuación total. Por ejemplo, imaginemos que un estudiante quiere sentarse en el *cluster 1*, *fila 2*, y que no quiere sentarse en el *asiento 4*. Si decidimos posicionarlo en el *cluster 3*, *fila 2* y *asiento 5*, esto sumará **2 PUNTOS** 🌠 a la puntuación total de la solución, ya que respetamos las preferencias de fila y asiento, pero no la preferencia de cluster.

### Preferencias relacionales

Las relaciones interpersonales también juegan un papel clave en las preferencias de los estudiantes. Como es normal, prefieren estar cerca de sus amigos, y lejos de las personas que no les agradan. Por este motivo, cada estudiante tiene otros dos estudiantes que quiere tener cerca (o lejos). La distancia entre estudiantes se mide a través de la distancia de Manhattan (ver https://en.wikipedia.org/wiki/Taxicab_geometry). Es decir, dados dos estudiantes **A** y **B** sentados en un mismo cluster, la distancia entre ellos se calculará como $|R_A-R_B|+|S_A-S_B|$, donde $(R_A,S_A)$ y $(R_B,S_B)$ son las filas y asientos en los que están sentados los estudiantes **A** y **B**, respectivamente. En caso de estar sentados en clusters distintos, la distancia entre ellos se considerará *infinita* a efectos prácticos.

Teniendo esto en cuenta, las preferencias relacionales puntuarán distinto según si se trata de una preferencia positiva o negativa:

- Si un estudiante **A** quiere tener *cerca* a otro estudiante **B**, obtendrá **3 PUNTOS** 🌠 si **B** está a distancia 1, **2 PUNTOS** 🌠 si **B** está a distancia 2, y **1 PUNTO** 🌠 si **B** está a distancia 3.
- Si un estudiante **A** quiere tener *lejos* a otro estudiante **B**, obtendrá **1 PUNTO** 🌠 si **B** está a distancia 2, **2 PUNTOS** 🌠 si **B** está a distancia 3, y **3 PUNTOS** 🌠 si **B** está a distancia 4 o más.

Por ejemplo, si el estudiante **A** sentado en el cluster 1, fila 2 y asiento 3 quiere tener cerca al estudiante **B** sentado en el cluster 1, fila 2 y asiento 5, sumará **2 PUNTOS** 🌠 a la puntuación total ya que la distancia entre ambos es 2.

### En resumen...

Tras encontrar una solución y subirla al juez online, se evaluarán los puntos otorgados por todos los estudiantes acomodados y se sumarán para obtener la puntuación final. En este paso, también se valorará la validez de la solución (*recuerda, por motivos legales, no es posible sentar a varios estudiantes en un mismo lugar*), por lo que no intentéis hacer trampas 🕵️‍♂️ Si bien dispondréis de herramientas para evaluar vuestras soluciones en local, la puntuación válida será la indicada por el juez online. La persona que encuentre la solución con una mayor puntuación total será la **GANADORA** del reto 👑

Recordad, la única regla es que no hay reglas. Podéis resolver el problema como queráis, siempre y cuándo entendáis lo que estáis haciendo, así que dad rienda suelta a vuestra creatividad. ¡Mucha suerte!

## Formato de los ficheros de datos 📄

### Instancia del problema

La instancia del problema que deberéis de resolver se encuentra en el fichero *students.csv* de la carpeta *data*. Este fichero contiene la información de las preferencias de los *192* estudiantes en formato **CSV**. Cada fila del fichero contiene la siguiente información:

- **ID:** Identificación del estudiante.
- **Cluster, Row, Seat:** Cluster/fila/asiento favorito si el valor es positivo, o cluster/fila/asiento no deseado si el valor es negativo.
- **Other_ID_1, Other_ID_2:** Identificación de los estudiantes con los que se tiene una preferencia de cercanía si el valor es positivo, o de lejanía si el valor es negativo.

La cantidad de clusters, filas y asientos disponibles en la instancia a resolver es 4, 8 y 6 respectivamente (para un total de *192* localizaciones).

### Solución al problema

Una vez implementado vuestro algoritmo para la resolución del problema, deberéis utilizar las utilidades disponibles en el código de la carpeta *src* para pasar vuestra solución a un formato **CSV** legible por parte del juez online. Cada fila de este fichero (el cuál, por defecto, se guardará en la carpeta *data*) deberá contener la siguiente información:

- **ID:** Identificación del estudiante.
- **Location:** Localización en la que colocar al estudiante, en formato c(**Nº cluster**)r(**Nº fila**)s(**Nº asiento**)

Una vez generado el fichero, deberéis subirlo al juez online para su valoración final.
