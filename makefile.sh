python3 preprocess.py
pdflatex -shell-escape notebook.tex
pdflatex -shell-escape notebook.tex
rm -f *.{aux,log,toc,fls,fdb_latexmk}
rm -rf _code/
