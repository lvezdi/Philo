hilos: procesos para ejecutar una sola accion
mutex: funcion que sirve para bloquear que dos datos se ejecuten en el mismo tiempo, para que no se sobrescriba
usleep: funcion para indicar el tiempo que van a dormir
get time: funcion o macro? para obtener el tiempo actual en el que se ha ejecutado. Esta funcion define que sean milisegundos.




todo los datos son int y son positivos, no letras ni caracteres raros
hilos del mutex e hilos a secas, chatgpt? tipo de datos distinto
cada filosofo tiene un hilo y cada tenedor tiene un hilo
parte basica del proyecto: se inicializa la estrucuta con :
- tiempo de vida, para comer, dormir, nº filosofo y veces que comen
- primera vez que empieza la simulación (como mesa redonda, necesitas saber si los filosofos son oares o impares, si es uno muere, esto dentro de una funcion que se crea de la divion entre dos de los filósofos)
- flag para saber cuando uno muere y dejan de comer, cuando uno come, las veces que come
estructura del philo:
- id philo para saber cuanod hay 
- cuantas veces tienen que comer
- ultima vez que han comido 
- hilo como tal (rutina y monitor(comprueba que no se muera ningun filosofoso y si muere se acaba la ejecución (liberas memoria, destruyes los hilos)))
- mutex tenedor derecho
- mutex tenedor izquierdo

estructura xxxx
- los 5 argumnetos 
- cuando acaba programa
- cuando acaba dormir

primeros pasos para empezar con el proyecto: 
PARSEO:
long, para que sea mas preciso al utilizar milisegundos
max filosofos 200
min 1
min milisegundos no menos de 60
no max milisegundos (long max con atoi)
arg no menos de 5 no max de 6
orden arg: 
◦ number_of_philosophers: es el número de filósofos, pero también el número
de tenedores.
◦ time_to_die (en milisegundos): si un filósofo no empieza a comer en time_to_die
milisegundos desde el comienzo de su ultima comida o desde el principio de la
simulación, este morirá.
◦ time_to_eat (en milisegundos): es el tiempo que tiene un filósofo para comer.
Durante ese tiempo, tendrá los tenedores ocupados.
◦ time_to_sleep (en milisegundos): es el tiempo que tiene un filósofo para
dormir.
◦ number_of_times_each_philosopher_must_eat (argumento opcional): si todos los filósofos comen al menos number_of_times_each_philosopher_must_eat
veces, la simulación se detendrá. Si no se especifica, la simulación se detendrá
con la muerte de un filósofo.
el último es opcional (que es una flag que añades)

is numeric
atoi 
init con estrutura 

El escenario:
- Hay N filósofos sentados en una mesa redonda.

- Entre cada filósofo hay un tenedor (por tanto, hay N tenedores).

- Para comer, un filósofo necesita dos tenedores: el de su izquierda y el de su derecha.

- Los filósofos alternan entre pensar, comer y dormir.

- Si un filósofo no come dentro de cierto tiempo, muere.

- La simulación termina si uno muere o si todos han comido el número de veces requerido.







- creando hilos e inicializarlo y asignar con id (quien empieza antes, mirar los turnos 2 o 3)


mutex para printear?


LOS FILOS EN HEAP (NO EN STACK PORQUE NO SABES CUANTOS)

ARRAY DE HILOS PARA INICIALIZARLOS 

MONITOR PARA VER SI LOS FILOSOFOS HAN MUERTO

QUE UN FILO MUERA NO SIGNIFICA QUE LE HLO TAMBIEN, SE COMPRUEBA CON PTHREAD_JOIN (NECEISTA HILO PARA QUE EL ACTUAL ESPERE A QUE TERMINE EL OTRO), EN EL HILO PRINCIPAL PORQUE PUEDE LIBERAR MEM SIN QUE HAYAN TERMINADO TODOS LOS HILOS
HILOS SON INT BOOLEANO 
QUE ACCEDEN CON TRUE O FALSE

MUTEX SOLO PARA COSAS QUE TENGAN PERMISOS DE LECTURA Y ESCRITURA
PROBLEMA CON LOS TURNOS:
2 PARA PARES 
3 PARA IMPARES


EN UNA ÚNICA FUNCION HACEN TODOS LA RUTINA Y QUE SE PEGUEN ENTRE ELLOS


una funcion que libere toda la memoria que creo

philo visualiter 

code vault youtube