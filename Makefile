.PHONY: clean all re see html

all: rubik.pdf 

rubik.pdf: rubik.tex
	pdflatex rubik.tex

clean:
	rm -f rubik.pdf
	rm -f rubik.aux
	rm -f rubik.log
	rm -rf html/*

re: clean all

see: all
	evince rubik.pdf

