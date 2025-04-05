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
  char ID[100] ;
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
  
  printf("Registrar nuevo ticket\n");
  printf("ID Ticket: ") ;
  scanf(" %s", tick->ID) ;
  
  printf("\n Descripcion del problema: ") ;
  scanf(" %s", tick->problema) ;

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
    actual = list_next(lista_tickets) ;
  }
  return NULL ;
}

void agregarCola(Queue *cola, ticket *tic){
  if (queue_front(cola) == NULL){
    queue_insert(cola, tic) ;
    return ;
  }
  List *lista = list_create() ;
  ticket *current = queue_remove(cola) ;
  while (current != NULL)
  {
    list_pushBack(lista, current) ;
    current = queue_remove(cola) ;
  }
  
  current = list_first(lista) ;

  while (current != NULL)
  {
    if (current->hora < tic->hora){
      queue_insert(cola, tic) ;
      queue_insert(cola, current) ;
    }
    else {
      queue_insert(cola, current) ;
    }
    current = list_next(lista) ;
  }
}


void funcionProvisional(ticket *tick, Queue *cola_agregar, Queue *colaPrioridad){
  List *listaAux = list_create() ;
  ticket *actual = queue_remove(colaPrioridad) ;
  while (actual != NULL){
    list_pushFront(listaAux, actual) ;
    actual = queue_remove(colaPrioridad) ;
  }
  actual = list_first(listaAux) ;
  while (actual != NULL){
    if (strcmp(actual->ID, tick->ID) == 0){
      printf("DEBUG CORRECTO!") ;
      presioneTeclaParaContinuar() ;
      agregarCola(cola_agregar, tick) ;
      actual = list_next(listaAux) ;
    }
    else {
      queue_insert(colaPrioridad, actual) ;
      actual = list_next(listaAux) ;
    }
  }
  


}

void asignar_prioridad(List *tickets, Queue *PB, Queue *PM, Queue *PA){
  char idTemp[100] ;
  char opcion ;
  printf("ID del ticket: ") ;
  
  scanf(" %s", idTemp) ;

  ticket *ticket_buscado = buscar_ticket(tickets, idTemp) ;
  while (ticket_buscado == NULL){
    char yn ;
    printf("Ticket no encontrado. ¿Quieres asignarle prioridad a otro ticket?\n") ;
    printf("1) Si\n") ;
    printf("2) No\n") ;
    scanf(" %c", &yn) ;
    if (yn == '2') return ;
    printf("ID del ticket: ") ;
    scanf(" %s", idTemp) ;
    ticket_buscado = buscar_ticket(tickets, idTemp) ;
  }

  printf("\n1) Prioridad Baja\n") ;
  printf("2) Prioridad Media\n") ;
  printf("3) Prioridad Alta\n") ;
  printf("Ingrese su opcion: ") ;
 
  scanf(" %c", &opcion) ;
  while (opcion < 49 || opcion > 51){
    printf("Opcion no valida, intente de nuevo :") ;
    scanf(" %c", &opcion) ;
  }

  if (ticket_buscado->prioridad == opcion) {
    printf("El ticket ya tiene esa prioridad\n") ;
    presioneTeclaParaContinuar() ;
    return ;
  }
  switch (opcion)
  {
    case '1':
      if (ticket_buscado->prioridad == '2') funcionProvisional(ticket_buscado, PB, PM) ; 
      else funcionProvisional(ticket_buscado, PB, PM) ;
      break;
    case '2' :
      if (ticket_buscado->prioridad == '1') funcionProvisional(ticket_buscado, PM, PB) ; 
      else funcionProvisional(ticket_buscado, PM, PA) ;
      break;
    case '3' :
      if (ticket_buscado->prioridad == '2') funcionProvisional(ticket_buscado, PA, PB) ; 
      else funcionProvisional(ticket_buscado, PA, PB) ;
      break;
  }
  printf("Prioridad asignada correctamente!") ;

}

void mostrarCola(Queue *cola){
  List *lista_auxiliar = list_create() ;
  ticket *current = queue_remove(cola) ;
  while (current != NULL)
  {
    printf("ID: %s problema = %s,", current->ID, current->problema) ;
    list_pushBack(lista_auxiliar, current) ;
    current = queue_remove(cola) ;
  }

  current = list_first(lista_auxiliar) ;
  while (current != NULL){
    queue_insert(cola, current) ;
    current = list_next(lista_auxiliar) ;
  }
  
}

void mostrar_lista_tickets(Queue *PB, Queue *PM, Queue *PA) {
  printf("Tickets en espera: \n");
  mostrarCola(PA) ;
  mostrarCola(PM) ;
  mostrarCola(PB) ; 
}

void atender_ticket(List *lista_tickets, Queue *PB, Queue *PM, Queue *PA){
  int count = 0 ;
  if (queue_front(PA) != NULL) {
    ticket *tick = queue_remove(PA) ;
    printf("Siguiente ticket: ID = %s Problema = %s\n", tick->ID, tick->problema) ;
    
    count ++ ;
  }
  else if (queue_front(PA) != NULL) {
    ticket *tick = queue_remove(PM) ;
    printf("Siguiente ticket: ID = %s Problema = %s\n", tick->ID, tick->problema) ;
    count ++ ;
  }
  else {
    ticket *tick = queue_remove(PB) ;
    printf("Siguiente ticket: ID = %s Problema = %s\n", tick->ID, tick->problema) ;
    count ++ ;
  }
  if (count == 0) printf("No se ha registrado ningun ticket.") ;
  presioneTeclaParaContinuar() ;
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
      atender_ticket(tickets, p_baja, p_media, p_alta) ;
      break;
    case '5':
      //buscar_ticket() ;
      break;
    case '6':
      puts("Saliendo del sistema de gestion de tickets...");
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
