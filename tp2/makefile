
ENTREGABLE=entregable.tar.gz

.PHONY: all tar help

all: help

tar: $(ENTREGABLE)

$(ENTREGABLE): informe
	make -C doc
	make clean -C backend
	tar -czf $@ backend -C informe informe.pdf

help:
	@echo "make         para compilar el backend"
	@echo "make tar     para generar el archivo entregable"

clean:
	rm -f $(ENTREGABLE)

