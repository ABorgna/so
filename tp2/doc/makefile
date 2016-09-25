targets = informe.pdf

includes = lock.tex backend.tex

LIBS = caratula.sty
DEPEND =

.PHONY: all clean

all: $(targets)

$(targets) : %.pdf : %.tex $(LIBS) $(DEPEND) $(includes)
	pdflatex $*
	pdflatex $*

clean:
	rm -f $(targets)
	rm -f *.aux
	rm -f *.log
	rm -f *.synctex.gz
	rm -f *.out
	rm -f *.xml
	rm -f *.bcf
	rm -f *.blg
	rm -f *.bbl
	rm -f informe-blx.bib
	rm -f *.toc
