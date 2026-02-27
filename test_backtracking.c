#include <stdio.h>
#include <stdlib.h>
#include "algoritmos.c"

int main() {
    
    int T = 50; 
    int n = 5;
    
    int tiempos[] = {32, 12, 21, 5, 17};
    int puntajes[] = {30, 21, 67, 32, 11};
    
    int* mejor_seleccion = (int*)malloc(n * sizeof(int));

    int puntaje_maximo = maximizar_puntaje_backtracking(n, T, tiempos, puntajes, mejor_seleccion);

    printf("Puntaje máximo: %d\n", puntaje_maximo);
    printf("Temas seleccionados: ");
    for(int i = 0; i < n; i++){
        if(mejor_seleccion[i] == 1){
            printf("%d ", i + 1);
        }
    }
    printf("\n");

    free(mejor_seleccion);
    return 0;
}