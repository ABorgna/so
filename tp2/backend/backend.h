#ifndef Backend_multi_h
#define Backend_multi_h

#include "casillero.h"
#include "encabezado.h"
#include "enviar_recibir.h"

#include <pthread.h>
#include <utility>  //pair

using namespace std;

bool cargar_int(const char* numero, unsigned int& n);

void atendedor_de_jugador(int* socket_fd);

// mensajes recibidos por el server
int recibir_nombre(int socket_fd, char* nombre);
int recibir_comando(int socket_fd, char* mensaje);
int parsear_casillero(char* mensaje, Casillero& ficha);

// mensajes enviados por el server
int enviar_dimensiones(int socket_fd);
int enviar_tablero(int socket_fd);
int enviar_ok(int socket_fd);
int enviar_error(int socket_fd);

// otras funciones
void cerrar_servidor(int signal);
void terminar_servidor_de_jugador(int socket_fd,
                                  list<Casillero>& jugada_actual);
void quitar_cartas(list<Casillero>& jugada_actual);
bool es_ficha_valida_en_jugada(const Casillero& ficha,
                               const list<Casillero>& jugada_actual);
Casillero casillero_mas_distante_de(const Casillero& ficha,
                                    const list<Casillero>& jugada_actual);
bool puso_carta_en(unsigned int fila, unsigned int columna,
                   const list<Casillero>& jugada_actual);

#endif
