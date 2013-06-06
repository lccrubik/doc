.PHONY: clean all re see html

all: rubik.pdf 

html: rubik.tex
	latex2html -v && latex2html -html_version 4.0,latin1,unicode rubik.tex -dir ./html

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

