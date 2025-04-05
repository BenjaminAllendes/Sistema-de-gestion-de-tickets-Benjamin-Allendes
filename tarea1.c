#include "list.h"
#include "stack.h"
#include "queue.h"
#include "extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct ticket{
  char prioridad ;
  char ID[6] ;
  char problema[100] ;
  time_t hora ;
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
  puts("5) Buscar ticket");
  puts("6) Salir");
}

void registrar_ticket(List *tickets, Queue *PB) {
  ticket *tick = (ticket *) malloc(sizeof(ticket)) ;
  if (tick == NULL) exit(EXIT_FAILURE) ;
  
  char ID_temp[6] ;
  printf("Registrar nuevo ticket\n");
  printf("ID Ticket: ") ;
  scanf(" %6s", tick->ID) ;
  
  printf("\n Descripcion del problema: ") ;
  scanf(" %100s", tick->problema) ;

  limpiarPantalla() ;
  tick->prioridad = '1' ;
  tick->hora = time(0) ;
  queue_insert(PB, tick) ;
  list_pushBack(tickets,tick) ;
  printf("Ticket registrado correctamente!\n") ;
}

ticket * buscar_ticket(List * lista_tickets, char *id){
  ticket * actual = list_first(lista_tickets) ;
  while (actual != NULL){
    if (strcmp(actual->ID, id) == 0) return actual ;
  }
  return NULL ;
}


void funcionProvisional(List *tickets, ticket *tick, Queue *colaPrioridad){
  Stack *pilaAux = stack_create(pilaAux) ;
  

}

void asignar_prioridad(List *tickets, Queue *PB, Queue *PM, Queue *PA){
  char idTemp[6] ;
  int opcion ;
  printf("ID del ticket: ") ;
  
  scanf(" %6s", idTemp) ;

  ticket *ticket_buscado = buscar_ticket(tickets, idTemp) ;
  while (ticket_buscado == NULL){
    char yn ;
    printf("Ticket no encontrado. ¿Quieres asignarle prioridad a otro ticket?\n") ;
    printf("1) Si\n") ;
    printf("2) No\n") ;
    scanf(" %c", &yn) ;
    if (yn == '2') return ;
    printf("ID del ticket: ") ;
    scanf(" %6s", idTemp) ;
    ticket_buscado = buscar_ticket(tickets, idTemp) ;
  }

  printf("\n1) Prioridad Baja\n") ;
  printf("2) Prioridad Media\n") ;
  printf("3) Prioridad Media\n") ;
  printf("Ingrese su opcion: ") ;
 
  scanf(" %c", opcion) ;
  while (opcion < 49 || opcion > 51){
    printf("Opcion no valida, intente de nuevo :") ;
    scanf(" %d", opcion) ;
  }

  if (ticket_buscado->prioridad == opcion) {
    printf("El ticket ya tiene esa prioridad") ;
    presioneTeclaParaContinuar() ;
    return ;
  }
  switch (opcion)
  {
    case '1':
      if (ticket_buscado-> prioridad == '2') funcionProvisional(tickets, ticket_buscado, PM) ; 
      else funcionProvisional(tickets, ticket_buscado, PA) ;
      break;
    case '2' :
      if (ticket_buscado-> prioridad == '1') funcionProvisional(tickets, ticket_buscado, PB) ; 
      else funcionProvisional(tickets, ticket_buscado, PA) ;
      break;
    case '3' :
      if (ticket_buscado-> prioridad == '2') funcionProvisional(tickets, ticket_buscado, PM) ; 
      else funcionProvisional(tickets, ticket_buscado, PB) ;
      break;
  }
  printf("Prioridad asignada correctamente!") ;
  presioneTeclaParaContinuar() ;

}

void mostrar_lista_tickets(Queue *PB, Queue *PM, Queue *PA) {
  printf("Tickets en espera: \n"); 
  // Aquí implementarías la lógica para recorrer y mostrar los pacientes
}

int main() {
  char opcion;
  List *tickets = list_create(); 
  Queue *p_baja = queue_create(p_baja) ;
  Queue *p_media = queue_create(p_media) ;
  Queue *p_alta = queue_create(p_alta) ;

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opcion: ");
    scanf(" %c", &opcion); 

    switch (opcion) {
    case '1':
      registrar_ticket(tickets, p_baja);
      break;
    case '2':
      asignar_prioridad(tickets, p_baja, p_media, p_alta) ;
      break;
    case '3':
      mostrar_lista_tickets(p_baja, p_media, p_alta);
      break;
    case '4':
      // Lógica para atender al siguiente paciente
      break;
    case '5':
      // Lógica para mostrar ticket
      break;
    case '6':
      puts("Saliendo del sistema de gestion hospitalaria...");
      break;
    default:
      puts("Opcion no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  // hacer variable para limpiar tickets !
  list_clean(tickets);

  return 0;
}
