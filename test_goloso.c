#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long iteraciones_bt = 0;      // No se usará
long long iteraciones_goloso = 0;  // Esta es la que importa aquí
long long iteraciones_dp = 0;      // No se usará

#include "algoritmos.c"


int REPETICIONES = 1000;
void ejecutar_test_goloso(int id_caso, int n, int T, int t[], int p[]) {
    printf("==================================================\n");
    printf("TEST GOLOSO CASO %d: n=%d, T=%d\n", id_caso, n, T);
    printf("==================================================\n");

    int* mejor_seleccion = (int*)malloc(n * sizeof(int));

    iteraciones_goloso = 0;
    int puntaje = Greedy(n, T, t, p, mejor_seleccion);
    
    printf("-> Puntaje Maximo (Goloso): %d\n", puntaje);
    printf("-> Tareas: ");
    for(int i=0; i<n; i++) {
        if(mejor_seleccion[i] != -1) printf("%d ", mejor_seleccion[i]);
    }
    printf("\n");

    const int REPS = 100000; 
    clock_t inicio = clock();
    for (int i = 0; i < REPS; i++) {
        Greedy(n, T, t, p, mejor_seleccion); 
    }
    clock_t fin = clock();

    double promedio = ((double)(fin - inicio) / CLOCKS_PER_SEC) / REPS;

    printf("-> Iteraciones: %lld\n", iteraciones_goloso);
    printf("-> Tiempo promedio: %.10f segundos\n\n", promedio);
    
    free(mejor_seleccion);
}

int main() {
    // CASO 1: Caso pequeño
    int n1 = 5, T1 = 15;
    int t1[] = {4, 3, 5, 2, 6};
    int p1[] = {12, 8, 15, 5, 20};
    ejecutar_test_goloso(1, n1, T1, t1, p1);

    // CASO 2: Contraejemplo del algoritmo goloso
    int n2 = 3, T2 = 50;
    int t2[] = {26, 25, 25};
    int p2[] = {260, 225, 225};
    ejecutar_test_goloso(2, n2, T2, t2, p2);

    // CASO 3: Escalabilidad medio (n = 15)
    int n3 = 15, T3 = 40;
    int t3[] = {5, 8, 3, 12, 6, 4, 9, 2, 7, 10, 5, 3, 8, 4, 6};
    int p3[] = {10, 15, 8, 25, 12, 9, 18, 5, 14, 20, 11, 7, 16, 10, 13};
    ejecutar_test_goloso(3, n3, T3, t3, p3);

    // CASO 4: Escalabilidad alto (n = 25)
    int n4 = 25, T4 = 60;
    int t4[] = {4, 6, 3, 8, 5, 2, 7, 4, 9, 5, 3, 6, 8, 2, 5, 7, 4, 9, 3, 6, 5, 8, 4, 7, 3};
    int p4[] = {8, 12, 5, 16, 9, 4, 15, 7, 18, 10, 6, 13, 17, 5, 11, 14, 9, 20, 7, 12, 10, 15, 8, 14, 6};
    ejecutar_test_goloso(4, n4, T4, t4, p4);

	// CASO 5: Caso de escalabilidad extremo (n = 40)
    int n5 = 40;
    int T5 = 100;
    int t5[] = {2, 3, 5, 7, 1, 4, 10, 8, 6, 12, 5, 3, 7, 2, 9, 11, 4, 8, 1, 6, 13, 5, 2, 7, 10, 4, 3, 8, 6, 11, 5, 2, 9, 7, 4, 12, 1, 8, 3, 6};
    int p5[] = {5, 8, 12, 18, 2, 10, 25, 20, 15, 30, 12, 7, 16, 4, 22, 28, 10, 19, 3, 14, 35, 12, 5, 16, 26, 9, 7, 20, 15, 29, 11, 5, 21, 18, 10, 32, 2, 18, 7, 15};
    ejecutar_test_goloso(5, n5, T5, t5, p5);

    return 0;
}

/*

Nota: Para ejecutar en consola, utilizar: 

gcc -Wall test_goloso.c -o test_goloso
./test_goloso

*/