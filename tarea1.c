#include "list.h"
#include "extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ticket{
  int prioridad ;
  char *ID ;
  int hora ;
} ticket ;

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestion de tickets");
  puts("========================================");

  puts("1) Registrar ticket");
  puts("2) Asignar prioridad a ticket");
  puts("3) Mostrar lista de tickets");
  puts("4) Atender al siguiente ticket"); 
  puts("5) Mostrar ticket por prioridad");
  puts("6) Salir");
}


void registrar_ticket(List *tickets) {
  ticket *tick = (ticket *) malloc(sizeof(ticket)) ;
  if (tick == NULL) exit(EXIT_FAILURE) ;
  
  char *ID_temp = (char *) malloc(sizeof(char) * 6) ;
  if (ID_temp == NULL) exit(EXIT_FAILURE) ;

  printf("Registrar nuevo ticket\n");
  
  scanf(" %6s", ID_temp) ;
  if (strlen(ID_temp) != 6){
    printf("Ticket debe tener exactamente 6 caracteres, ingrese nuevamente\n") ;
    scanf(" %6s", ID_temp) ;
  }
  tick->ID = ID_temp ;
  tick->prioridad = 1 ;
  list_pushBack(tickets,tick) ;
}

void mostrar_lista_tickets(List *tickets) {
  // Mostrar pacientes en la cola de espera
  printf("Tickets en espera: \n"); 
  // Aquí implementarías la lógica para recorrer y mostrar los pacientes
}

int main() {
  char opcion;
  List *tickets = list_create(); // puedes usar una lista para gestionar los pacientes

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opcion: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_ticket(tickets);
      break;
    case '2':
      // Lógica para asignar prioridad
      break;
    case '3':
      mostrar_lista_tickets(tickets);
      break;
    case '4':
      // Lógica para atender al siguiente paciente
      break;
    case '5':
      // Lógica para mostrar pacientes por prioridad
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opcion no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(tickets);

  return 0;
}
