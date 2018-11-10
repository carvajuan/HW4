Resultados_hw4.pdf: 45_grados.pdf angulos.pdf Resultados_hw4.tex
	pdflatex Resultados_hw4.tex

45_grados.pdf: 45.txt Plots_hw4.py
	python Plots_hw4.py

angulos.pdf: angulo.txt Plots_hw4.py
	python Plots_hw4.py

45.txt: a.out
	./a.out 

angulo.txt: a.out 
	./a.out 

a.out: ODE.cpp
	g++ ODE.cpp
