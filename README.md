# Codigo para lista de espera de un hospital con prioridad

<br>
<br>

Para ejecutar el codigo hay que usar estos comandos:
````console
gcc tdas/*.c main.c -Wno-unused-result -o main
````

Y luego ejecutar:
````console
./main
````

<br>

<hr>

El codigo te abre un menu donde tu eliges que opcion te interesa.

````bash
1) Registrar paciente `nombre_del_paciente`, `edad`, `sintoma`
2) Asignar prioridad al paciente `ALTA`, `MEDIA`, `BAJA`
3) Mostrar lista de espera
4) Atender al siguiente paciente
5) Mostrar paciente por prioridad `ALTA`, `MEDIA`, `BAJA`
6) Exit
````

El funcionamiento es simple, crea un struct donde almacenan los distintos datos necesarios y ahi crea el array global con tipo de dato del struct.

````c
struct listaP {
  char nombre[50];
  char sintoma[200];
  int edad;
  int prioridad;
  time_t hora;
};

struct listaP *data = NULL;
````

**NOTA*** Tambien se usa la zona horario donde te encuentras para registrar la hora actual y ponerla en cada paciente al registrarse.

<br>

### Prototipos de funciones principales


`void mostrarMenuPrincipal();`

`void registrar_paciente();`

`void asignar_prioridad();`

`void mostrar_lista_pacientes();`

`void eliminar_paciente();`

`void mostrar_prioridad_pacientes();`


Todas las funciones son sin argumentos porque hice un array global donde se cambia en todo el codigo y no hay necesidad de poner argumentos.

<br>

<hr>

### Ordenamiento del array por prioridad y hora

Para ordenar el array yo utilice **qsort** para facilitar el proceso y ser mas eficiente, cree una funcion para comparar la prioridad y si son iguales por la hora y despues se ordenan al llamar al qsort en `mostrar_lista_pacientes`.

````c
int comparar_pacientes(const void *a, const void *b) //prototipo de la funcion comparar
````
````c
qsort(data, count, sizeof(struct listaP), comparar_pacientes); //funcion qsort para ordenar de mayor a menor
````
<br>

### Observaciones
- Por defecto si no le pones ninguna prioridad a un paciente, quedara en **BAJA** por default.
- El codigo cuando te piden ingresar una opcion que son numeros y tu agregas una letra va a arrojar `Segmentation fault (core dumped)`.
- Si a la edad ingresas un valor no válido como un caracter va a quedar por defecto en 0 años.
- Al querer cambiar la prioridad de un paciente, el nombre tiene que ser exactamente igual al registrado, si no, no lo encontrara.
- Si le agregas una prioridad a un paciente que no existe tambien arrojara `Segmentation fault (core dumped)`.

<br>

<br>

###### 💻 | Development By Sarwak




