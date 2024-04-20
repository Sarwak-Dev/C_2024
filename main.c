#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estructura de paciente
struct listaP {
  char nombre[50];
  char apellido[50];
  char sintoma[200];
  int edad;
  int prioridad;
  time_t hora;
};

int count = 0;
struct listaP *data = NULL;

int comparar_pacientes(const void *a, const void *b) {
  const struct listaP *pacienteA = (const struct listaP *)a;
  const struct listaP *pacienteB = (const struct listaP *)b;

  // Ordenar primero por prioridad de mayor a menor
  if (pacienteA->prioridad != pacienteB->prioridad) {
    return pacienteB->prioridad - pacienteA->prioridad;
  }
  // Si la prioridad es la misma, ordenar por hora de menor a mayor
  else {
    return pacienteA->hora - pacienteB->hora;
  }
}

// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}

// Función para registrar pacientes automáticamente
void registrar_paciente() {

  if (count == 0) {
    data = (struct listaP *)malloc(sizeof(struct listaP));
  }

  else {
    data = (struct listaP *)realloc(data, sizeof(struct listaP) * (count + 1));
  }

  char default_string[] = "NULL";

  printf("Registre el nuevo paciente\n");

  printf("Nombre del paciente\n");
  scanf(" %[^\n]", data[count].nombre);

  printf("Edad del paciente\n");
  // scanf("%d", &data[count].edad);
  if (scanf("%d", &data[count].edad) == EOF) {
    data[count].edad = 0;
  }

  printf("Sintoma del paciente\n");
  scanf(" %[^\n]", data[count].sintoma);

  data[count].prioridad = 0;
  data[count].hora = time(NULL);

  // list_pushBack(pacientes, &data);
  count++;
  
}

void asignar_prioridad() {
  int prioridad;
  int temp;
  char nombre[50];

  printf("Ingrese el nombre del paciente que quiere cambiar la prioridad:\n\n");
  scanf(" %[^\n]", nombre);

  for (int i = 0; i < count; i++) {
    if (strcmp(data[i].nombre, nombre) == 0) {
      temp = i;
    }
  }
  
  printf("Ingrese la nueva prioridad del paciente:\n\n");

  printf("1) ALTA | Solo si su paciente necesita urgencia de inmediata!\n\n");
  printf("2) MEDIA | Si su paciente necesita tratamiento lo mas rapido posible.\n\n");
  printf("3) BAJA | Si su paciente tiene algo menor y puede esperar.\n\n");

  scanf("%d", &prioridad);
  data[temp].prioridad = prioridad;

  if (prioridad == 1) {
    data[temp].prioridad = 2;
    printf("Se le ha asigando con exito la prioridad de |ALTA| al paciente");
  }

  else if (prioridad == 2) {
    data[temp].prioridad = 1;
    printf("Se le ha asigando con exito la prioridad de |MEDIA| al paciente");
  }

  else if (prioridad == 3) {
    data[temp].prioridad = 0;
    printf("Se le ha asigando con exito la prioridad de |BAJA| al paciente");
  }
}

void mostrar_lista_pacientes() {
  // Mostrar pacientes en la cola de espera
  printf("====================\n");
  printf("Pacientes en espera: \n");
  printf("====================\n\n");

  for (int i = 0; i < count; i++) {
    printf("Hora del paciente:\n");
    struct tm *local = localtime(&data[i].hora);
    printf("%02d:%02d:%02d\n\n", local->tm_hour, local->tm_min, local->tm_sec);

    printf("Nombre y Apellido del paciente:\n");
    printf("- %s %s\n\n", data[i].nombre, data[i].apellido);

    printf("Edad del paciente:\n");
    printf("- %d\n\n", data[i].edad);

    printf("Prioridad de espera:\n");
    if (data[i].prioridad == 1)
      printf("- MEDIA\n\n");

    else if (data[i].prioridad == 2)
      printf("- ALTA\n\n");

    else if (data[i].prioridad == 0)
      printf("- BAJA\n\n");

    printf("Sintoma del paciente:\n");
    printf("- %s\n\n", data[i].sintoma);
    printf("<-------------------->\n\n");
  }
  // Aquí implementarías la lógica para recorrer y mostrar los pacientes
}

void eliminar_paciente() {
    // Verificar si la lista está vacía
    if (count == 0) {
        printf("No hay pacientes para eliminar.\n");
        return;
    }
  
    printf("Hora del paciente:\n");
    struct tm *local = localtime(&data[0].hora);
    printf("%02d:%02d:%02d\n\n", local->tm_hour, local->tm_min, local->tm_sec);

    printf("Nombre y Apellido del paciente:\n");
    printf("- %s %s\n\n", data[0].nombre, data[0].apellido);

    printf("Edad del paciente:\n");
    printf("- %d\n\n", data[0].edad);

    printf("Prioridad de espera:\n");
    if (data[0].prioridad == 1)
      printf("- MEDIA\n\n");

    else if (data[0].prioridad == 2)
      printf("- ALTA\n\n");

    else if (data[0].prioridad == 0)
      printf("- BAJA\n\n");

    printf("Sintoma del paciente:\n");
    printf("- %s\n\n", data[0].sintoma);
    printf("<-------------------->\n\n");

    // Mover todos los pacientes una posición hacia atrás
    for (int i = 0; i < count - 1; i++) {
        data[i] = data[i + 1];
    }

    // Reducir el contador de pacientes
    count--;

    printf("Paciente eliminado con éxito.\n");

    // No es necesario liberar la memoria ya que no hemos asignado nuevos bloques de memoria
}

void mostrar_prioridad_pacientes() {
  int opcion;
  
  printf("====================\n");
  printf("Selecciona una opcion: \n");
  printf("====================\n\n");

  printf("1) Mostrar pacientes con prioridad ALTA\n\n");
  printf("2) Mostrar pacientes con prioridad MEDIA\n\n");
  printf("3) Mostrar pacientes con prioridad BAJA\n\n");
  scanf(" %d", &opcion);

  if (opcion == 1) {
    for (int i = 0; i < count; i++) {
      if (data[i].prioridad == 2) {
        printf("Hora del paciente:\n");
        struct tm *local = localtime(&data[i].hora);
        printf("%02d:%02d:%02d\n\n", local->tm_hour, local->tm_min, local->tm_sec);
  
        printf("Nombre y Apellido del paciente:\n");
        printf("- %s %s\n\n", data[i].nombre, data[i].apellido);
  
        printf("Edad del paciente:\n");
        printf("- %d\n\n", data[i].edad);
  
        printf("Prioridad de espera:\n");
        printf("- ALTA\n\n");
      }
    }
  }

  else if (opcion == 2) {
    for (int i = 0; i < count; i++) {
      if (data[i].prioridad == 1) {
        printf("Hora del paciente:\n");
        struct tm *local = localtime(&data[i].hora);
        printf("%02d:%02d:%02d\n\n", local->tm_hour, local->tm_min, local->tm_sec);
  
        printf("Nombre y Apellido del paciente:\n");
        printf("- %s %s\n\n", data[i].nombre, data[i].apellido);
  
        printf("Edad del paciente:\n");
        printf("- %d\n\n", data[i].edad);
  
        printf("Prioridad de espera:\n");
        printf("- MEDIA\n\n");
      }
    }
  }

  else if (opcion == 3) {
    for (int i = 0; i < count; i++) {
      if (data[i].prioridad == 0) {
        printf("Hora del paciente:\n");
        struct tm *local = localtime(&data[i].hora);
        printf("%02d:%02d:%02d\n\n", local->tm_hour, local->tm_min, local->tm_sec);
  
        printf("Nombre y Apellido del paciente:\n");
        printf("- %s %s\n\n", data[i].nombre, data[i].apellido);
  
        printf("Edad del paciente:\n");
        printf("- %d\n\n", data[i].edad);
  
        printf("Prioridad de espera:\n");
        printf("- BAJA\n\n");
      }
    }
  }
  else {
    printf("Opcion invalida");
  }
}

int main() {
  srand(time(NULL));
  // Ordenar la lista de pacientes

  char opcion;

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      limpiarPantalla();
      registrar_paciente();
      break;

    case '2':
      limpiarPantalla();
      asignar_prioridad();
      break;

    case '3':
      limpiarPantalla();
      qsort(data, count, sizeof(struct listaP), comparar_pacientes);
      mostrar_lista_pacientes();
      break;

    case '4':
      limpiarPantalla();
      eliminar_paciente();
      break;

    case '5':
      limpiarPantalla();
      mostrar_prioridad_pacientes();
      break;

    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;

    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  // list_clean();

  return 0;
}

/*


#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct listaP {
  char nombre[50];
  char apellido[50];
  char sintoma[200];
  int edad;
  int prioridad;
  int id;
};

int count = 0;
struct listaP *data = NULL;

int comparar_pacientes(const void *a, const void *b) {
  const struct listaP *pacienteA = (const struct listaP *)a;
  const struct listaP *pacienteB = (const struct listaP *)b;

  // Ordenar primero por prioridad de mayor a menor
  if (pacienteA->prioridad != pacienteB->prioridad) {
    return pacienteB->prioridad - pacienteA->prioridad;
  }
  // Si la prioridad es la misma, ordenar por ID de menor a mayor
  else {
    return pacienteA->id - pacienteB->id;
  }
}

// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}

void registrar_paciente() {

  if (count == 0) {
    data = (struct listaP *)malloc(sizeof(struct listaP));
  }

  else {
    data = (struct listaP *)realloc(data, sizeof(struct listaP) * (count + 1));
  }

  char default_string[] = "NULL";

  printf("Registre el nuevo paciente\n");

  printf("Nombre del paciente (Sin apellido)\n");
  scanf("%[^ ]", data[count].nombre);
  if (strlen(data[count].nombre) == 0) {
    strcpy(data[count].nombre, default_string);
  }

  printf("Apellido del paciente\n");
  scanf("%49s", data[count].apellido);
  if (strlen(data[count].apellido) == 0) {
    strcpy(data[count].apellido, default_string);
  }

  printf("Edad del paciente\n");
  // scanf("%d", &data[count].edad);
  if (scanf("%d", &data[count].edad) == EOF) {
    data[count].edad = 0;
  }

  printf("Sintoma del paciente\n");
  scanf("%[^ ]", data[count].sintoma);
  if (strlen(data[count].sintoma) == 0) {
    strcpy(data[count].sintoma, default_string);
  }
  data[count].prioridad = 0;
  data[count].id = count;

  // list_pushBack(pacientes, &data);
  count++;
}

void asignar_prioridad() {
  int prioridad;

  printf("Ingrese la prioridad del paciente:\n\n");

  printf("1) ALTA | Solo si su paciente necesita urgencia de inmediata!\n\n");
  printf("2) MEDIA | Si su paciente necesita tratamiento lo mas rapido "
         "posible.\n\n");
  printf("3) BAJA | Si su paciente tiene algo menor y puede esperar.\n\n");
  scanf(" %d", &prioridad);

  if (prioridad == 1) {
    data[count - 1].prioridad = 2;
    printf("Se le ha asigando con exito la prioridad de |ALTA| al paciente");
  }

  else if (prioridad == 2) {
    data[count - 1].prioridad = 1;
    printf("Se le ha asigando con exito la prioridad de |MEDIA| al paciente");
  }

  else if (prioridad == 3) {
    data[count - 1].prioridad = 0;
    printf("Se le ha asigando con exito la prioridad de |BAJA| al paciente");
  }
}

void mostrar_lista_pacientes() {
  // Mostrar pacientes en la cola de espera
  printf("====================\n");
  printf("Pacientes en espera: \n");
  printf("====================\n\n");

  for (int i = 0; i < count; i++) {
    printf("ID del paciente:\n");
    printf("- %d\n\n", data[i].id);

    printf("Nombre y Apellido del paciente:\n");
    printf("- %s %s\n\n", data[i].nombre, data[i].apellido);

    printf("Edad del paciente:\n");
    printf("- %d\n\n", data[i].edad);

    printf("Prioridad de espera:\n");
    if (data[i].prioridad == 1)
      printf("- MEDIA\n\n");

    else if (data[i].prioridad == 2)
      printf("- ALTA\n\n");

    else if (data[i].prioridad == 0)
      printf("- BAJA\n\n");

    printf("Sintoma del paciente:\n");
    printf("- %s\n\n", data[i].sintoma);
    printf("<-------------------->\n\n");
  }
  // Aquí implementarías la lógica para recorrer y mostrar los pacientes
}

void mostrar_prioridad_pacientes() {
  printf("====================\n");
  printf("Pacientes en espera: \n");
  printf("====================\n\n");

  for (int i = 0; i < count; i++) {
    printf("ID del paciente:\n");
    printf("- %d\n", data[i].id);
    printf("Nombre y Apellido del paciente:\n");
    printf("- %s %s\n", data[i].nombre, data[i].apellido);
    printf("Edad del paciente:\n");
    printf("- %d\n", data[i].edad);
    printf("Prioridad de espera:\n");
    if (data[i].prioridad == 2)
      printf("- ALTA\n");
    else if (data[i].prioridad == 1)
      printf("- MEDIA\n");
    else if (data[i].prioridad == 0)
      printf("- BAJA\n");
    printf("Sintoma del paciente:\n");
    printf("- %s\n", data[i].sintoma);
    printf("<-------------------->\n\n");
  }
}

int main() {

  // Ordenar la lista de pacientes

  char opcion;

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      limpiarPantalla();
      registrar_paciente();
      break;

    case '2':
      limpiarPantalla();
      asignar_prioridad();
      break;

    case '3':
      limpiarPantalla();
      mostrar_lista_pacientes();
      break;

    case '4':

      break;

    case '5':
      limpiarPantalla();
      qsort(data, count, sizeof(struct listaP), comparar_pacientes);
      mostrar_prioridad_pacientes();
      break;

    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;

    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  // list_clean();

  return 0;
}

*/