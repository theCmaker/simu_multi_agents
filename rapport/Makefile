CC=pdflatex
CFLAGS=-shell-escape
CONFIG=settings/*.tex
OBJS=titlepage.tex doxygen.tex git.tex presentation.tex developpement.tex conclusion.tex diagramme_gantt_init.tex diagramme_gantt_final.tex resultats.tex
JOBNAME=compte_rendu

$(JOBNAME).pdf: $(JOBNAME).tex $(CONFIG) $(OBJS)
	$(CC) $(CFLAGS) $< ;

clean: 
	rm -rf _minted-$(JOBNAME) *~ $(JOBNAME).aux $(JOBNAME).toc $(JOBNAME).log $(JOBNAME).bbl $(JOBNAME).blg $(JOBNAME).gz $(JOBNAME).out $(JOBNAME)-*.asy $(JOBNAME)-*.pdf $(JOBNAME).pre $(JOBNAME).vrb $(JOBNAME).snm
