# Variables para el compilador y banderas
CC = gcc
CFLAGS = -Wall -O3

# Nombres de los ejecutables
TARGETS = test_backtracking test_goloso test_dinamico

# Regla por defecto: compila los tres programas
all: $(TARGETS)

# Reglas para compilar cada test de forma individual
test_backtracking: test_backtracking.c algoritmos.c
	$(CC) $(CFLAGS) test_backtracking.c -o test_backtracking

test_goloso: test_goloso.c algoritmos.c
	$(CC) $(CFLAGS) test_goloso.c -o test_goloso

test_dinamico: test_dinamico.c algoritmos.c
	$(CC) $(CFLAGS) test_dinamico.c -o test_dinamico

# Regla para ejecutar todas las pruebas de una vez
run: all
	@echo "Ejecutando prueba de Backtracking..."
	./test_backtracking
	@echo "\nEjecutando prueba de Algoritmo Goloso..."
	./test_goloso
	@echo "\nEjecutando prueba de Programacion Dinamica..."
	./test_dinamico

# Limpiar los archivos ejecutables creados
clean:
	rm -f $(TARGETS)