#ifndef Casillero_h
#define Casillero_h

#include "encabezado.h"

struct Casillero {
    Casillero() : fila(0), columna(0), contenido(VACIO){};
    // Casillero(unsigned int _fila, unsigned int _columna, char _letra) :
    // fila(_fila), columna(_columna), letra(_letra) {};

    unsigned int fila;
    unsigned int columna;
    char contenido;
};

#endif
