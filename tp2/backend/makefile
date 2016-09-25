CC = g++
CFLAGS = -g -Wall -Wextra -std=c++11
LDFLAGS = -pthread

BINARIES = backend

all: $(BINARIES)

backend: backend.cpp backend.h enviar_recibir.o enviar_recibir.h encabezado.h casillero.h locks/RWLock.h locks/RWLock.o
	$(CC) $(LDFLAGS) $(CFLAGS) backend.cpp enviar_recibir.o locks/RWLock.o -o $@

enviar_recibir.o: enviar_recibir.cpp enviar_recibir.h encabezado.h
	$(CC) $(CFLAGS) -o $@ -c $<

locks/RWLock.o: locks/RWLock.cpp locks/RWLock.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o
	rm -f locks/*.o
	rm -f $(BINARIES)
