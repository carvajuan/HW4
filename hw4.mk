Resultados_hw4.pdf: 45.jpg Angulos.jpg 1_fijas.jpg 2_fijas.jpg 1_abiertas.jpg 2_abiertas.jpg 1_periodicas.jpg 2_periodicas.jpg Momento_inicial.jpg Fronteras_fijas.jpg Fronteras_abiertas.jpg Fronteras_periodicas.jpg Temperatura_promedio.jpg Resultados_hw4.tex
	pdflatex Resultados_hw4.tex

45.jpg Angulos.jpg: 45.txt angulo.txt Plots_hw4.py
	python Plots_hw4.py

1_fijas.jpg 2_fijas.jpg 1_abiertas.jpg 2_abiertas.jpg 1_periodicas.jpg 2_periodicas.jpg Momento_inicial.jpg Fronteras_fijas.jpg Fronteras_abiertas.jpg Fronteras_periodicas.jpg Temperatura_promedio.jpg: Temperatura_promedio.txt Temperatura_inicial.txt Fronteras_fijas.txt Fronteras_abiertas.txt Fronteras_periodicas.txt Graficas.txt Plots_hw4.py
	python Plots_hw4.py

45.txt angulo.txt: punto1.x
	./punto1.x

Temperatura_promedio.txt Temperatura_inicial.txt Fronteras_fijas.txt Fronteras_abiertas.txt Fronteras_periodicas.txt Graficas.txt: punto2.x
	./punto2.x
	
punto1.x : ODE.cpp
	g++ ODE.cpp -o punto1.x
	
punto2.x: PDE.cpp
	g++ PDE.cpp -o punto2.x
