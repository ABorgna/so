
ENTREGABLE=entregable.tar.gz

.PHONY: all tar help

all: help

tar: $(ENTREGABLE)

$(ENTREGABLE): informe
	make -C simusched clean
	make -C informe
	tar -czf $@ simusched -C informe informe.pdf

help:
	@echo "make tar 	para generar el archivo entregable"

clean:
	rm -f $(ENTREGABLE)

