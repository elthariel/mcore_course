MAIN = slides.tex
DEPS = $(wildcard ./*.tex)

all: slides.pdf

slides.pdf: $(DEPS)
	pdflatex -shell-escape $(MAIN)
	pdflatex -shell-escape $(MAIN)

clean:
	rm -f slides.pdf
	rm -f *~

.PHONY: all clean
