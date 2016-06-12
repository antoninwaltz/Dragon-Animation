LATEX := pdflatex
TARGET := IN55.pdf

.PHONY: all clean distclean

all: $(TARGET)

%.pdf: %.tex
	echo "Building pdf"
	$(LATEX) --shell-escape $<
	rm -f $@
	$(LATEX) --shell-escape $<

clean:
	rm -f *.log *.nav *.snm *.aux *.out *.toc *.pyg *.lof

distclean: clean
	rm -f $(TARGET)
