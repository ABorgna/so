#ifndef Encabezado_h
#define Encabezado_h

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <list>
#include <vector>

#define PORT 5481

#define MENSAJE_MAXIMO 1024
#define DATO_MAXIMO 100

#define VACIO 0x20
#define RESERVADO 0x01
#define CORAZON 0x43
#define PICA 0x50
#define TREBOL 0x54
#define DIAMANTE 0x44

#define MSG_CARTA 1
#define MSG_CONFIRMO 2
#define MSG_UPDATE 3
#define MSG_INVALID 99

int recibir(int s, char* buf);
int enviar(int s, char* buf);

#endif
