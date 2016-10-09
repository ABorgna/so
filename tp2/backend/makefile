CC = g++
CFLAGS = -g -Wall -Wextra -std=c++11
LDFLAGS = -pthread

BINARIES = backend
TEST_BIN = locks/test

all: $(BINARIES)

test: $(TEST_BIN)
	$<

backend: backend.cpp backend.h enviar_recibir.o enviar_recibir.h encabezado.h casillero.h locks/RWLock.h locks/RWLock.o
	$(CC) $(LDFLAGS) $(CFLAGS) backend.cpp enviar_recibir.o locks/RWLock.o -o $@

enviar_recibir.o: enviar_recibir.cpp enviar_recibir.h encabezado.h
	$(CC) $(CFLAGS) -o $@ -c $<

locks/RWLock.o: locks/RWLock.cpp locks/RWLock.h
	$(CC) $(CFLAGS) -o $@ -c $<

locks/test: locks/test.cpp locks/RWLock.o
	$(CC) $(LDFLAGS) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o
	rm -f locks/*.o
	rm -f $(BINARIES)
	rm -f $(TEST_BIN)
