targets = informe.pdf

includes = ej1.tex ej2.tex ej3.tex ej4.tex ej5.tex ej6.tex \
		   ej7.tex ej8.tex ej9.tex

libs = caratula.sty

all: $(targets)

$(targets) : %.pdf : %.tex $(libs) $(includes)
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
