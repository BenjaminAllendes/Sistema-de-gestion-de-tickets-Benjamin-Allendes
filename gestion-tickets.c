#include "list.h"
#include "queue.h"
#include "extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct ticket{
  char prioridad ;
  char ID[100] ;
  char problema[1000] ;
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

ticket * buscar_ticket(List * lista_tickets, char *id){
  ticket * actual = list_first(lista_tickets) ;
  while (actual != NULL){
    if (strcmp(actual->ID, id) == 0) return actual ;
    actual = list_next(lista_tickets) ;
  }
  return NULL ;
}

void registrar_ticket(List *tickets, List *PB) {
  ticket *tick = (ticket *) malloc(sizeof(ticket)) ;
  if (tick == NULL) exit(EXIT_FAILURE) ;
  
  printf("Registrar nuevo ticket");
  printf("\nID Ticket: ") ;
  scanf(" %[^\n]s", tick->ID) ;
  if (buscar_ticket(tickets, tick->ID) != NULL) {
    printf("Este ticket ya ha sido registrado!\n") ;
    free(tick) ; 
    return ;
  }
  printf("\nDescripcion del problema: ") ;
  scanf(" %[^\n]s", tick->problema) ;
  getchar() ;
  limpiarPantalla() ;
  tick->prioridad = '1' ;
  tick->hora = time(0) ;
  list_pushBack(PB, tick) ;
  list_pushBack(tickets,tick) ;
  printf("Ticket registrado correctamente!\n") ;
}

void mover_ticket(ticket *tick, List *lista_agregar, List *lista_prioridad){
  ticket *actual = list_first(lista_prioridad) ;
  while (actual != tick){
    actual = list_next(lista_prioridad) ;
  }  
  printf("Otro debug") ;
  presioneTeclaParaContinuar() ;
  ticket *aux = list_popCurrent(lista_prioridad) ;
  if (list_size(lista_agregar) == 0){
    list_pushBack(lista_agregar, tick) ;
    return ;
  }
  actual = list_first(lista_agregar) ;
  while (actual != NULL)
  {
    if (actual->hora > aux->hora)
    {
      list_pushCurrent(lista_agregar, aux) ;
      return ;
    }       
    actual = list_next(lista_agregar) ;
  }
  list_pushBack(lista_agregar, aux) ;
  

}

void asignar_prioridad(List *tickets, List *PB, List *PM, List *PA){
  char idTemp[100] ;
  char opcion ;
  printf("ID del ticket: ") ;
  
  scanf(" %s", idTemp) ;

  ticket *ticket_buscado = buscar_ticket(tickets, idTemp) ;
  while (ticket_buscado == NULL){
    char yn ;
    printf("Ticket no encontrado. Quieres asignarle prioridad a otro ticket?\n") ;
    printf("1) Si\n") ;
    printf("2) No\n") ;
    scanf(" %c", &yn) ;
    if (yn == '2') return ;
    limpiarPantalla() ;
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
    return ;
  }

  printf("debugini") ;
  presioneTeclaParaContinuar() ;

  switch (opcion)
  {
    case '1':
      
      if (ticket_buscado->prioridad == '2') mover_ticket(ticket_buscado, PB, PM) ; 
      else mover_ticket(ticket_buscado, PB, PM) ;
      ticket_buscado->prioridad = '1' ;
      break;
    case '2' :
      
      if (ticket_buscado->prioridad == '1') mover_ticket(ticket_buscado, PM, PB) ; 
      else mover_ticket(ticket_buscado, PM, PA) ;
      ticket_buscado->prioridad = '2' ;
      break;
      
    case '3' :
      
      if (ticket_buscado->prioridad == '2') mover_ticket(ticket_buscado, PA, PB) ; 
      else mover_ticket(ticket_buscado, PA, PB) ;
      ticket_buscado->prioridad = '3' ;
      break;
  }
  printf("Prioridad asignada correctamente!") ;

}

void mostrarLista(List *L){
  List *lista_auxiliar = list_create() ;
  ticket *current = list_first(L) ;
  while (current != NULL)
  {
    printf("ID: %s problema = %s,", current->ID, current->problema) ;
    current = list_next(L) ;
  }
}

void mostrar_lista_tickets(List *listatickets, List *PB, List *PM, List *PA) {
  if (list_first(listatickets) == NULL) {
    printf("No se ha registrado ningun ticket\n") ;
    return ;
  }
  printf("Tickets en espera: \n");
  mostrarLista(PA) ;
  mostrarLista(PM) ;
  mostrarLista(PB) ; 
  printf("\n") ;
}

void eliminarTicket(List *lista_tickets, ticket *tick) {
  ticket *current = list_first(lista_tickets) ;
  while (current != tick) {
    current = list_next(lista_tickets) ;
  }
  list_popCurrent(lista_tickets) ;
}

void atender_ticket(List *lista_tickets, List *PB, List *PM, List *PA){
  int count = 0 ;
  if (queue_front(PA) != NULL) {
    ticket *tick = list_popFront(PA) ;
    printf("Siguiente ticket: ID = %s Problema = %s\n", tick->ID, tick->problema) ;
    eliminarTicket(lista_tickets, tick) ;
    count ++ ;
  }
  else if (queue_front(PM) != NULL) {
    ticket *tick = list_popFront(PM) ;
    printf("Siguiente ticket: ID = %s Problema = %s\n", tick->ID, tick->problema) ;
    eliminarTicket(lista_tickets, tick) ;
    count ++ ;
  }
  else if (queue_front(PB) != NULL){
    ticket *tick = list_popFront(PB) ;
    printf("Siguiente ticket: ID = %s Problema = %s\n", tick->ID, tick->problema) ;
    eliminarTicket(lista_tickets, tick) ;
    count ++ ;
  }
  if (count == 0) printf("No se ha registrado ningun ticket.\n") ;
}

void buscar_mostrar_ticket(List *ticketos){
  char idTicket[100] ;
  printf("ID del ticket: ") ;
  scanf(" %s", idTicket) ;
  ticket *tick = buscar_ticket(ticketos, idTicket) ;
  if (tick == NULL){
    printf("No existe un ticket con ese ID.\n") ;
    return ;
  }
  printf("\nInformacion Del ticket '%s':", tick->ID) ;
  struct tm * timeinfo;
  timeinfo = localtime(&tick->hora) ;
  printf("\nHora = %s", asctime(timeinfo)) ;
  printf("Problema = %s\n", tick->problema) ;

}

int main() {
  char opcion;
  List *tickets = list_create(); 
  List *p_baja = queue_create(p_baja) ;
  List *p_media = queue_create(p_media) ;
  List *p_alta = queue_create(p_alta) ;

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
      mostrar_lista_tickets(tickets, p_baja, p_media, p_alta);
      break;
    case '4':
      atender_ticket(tickets, p_baja, p_media, p_alta) ;
      break;
    case '5':
      buscar_mostrar_ticket(tickets) ;
      break;
    case '6':
      puts("Saliendo del sistema de gestion de tickets...");
      break;
    default:
      puts("Opcion no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  list_clean(tickets);

  return 0;
}