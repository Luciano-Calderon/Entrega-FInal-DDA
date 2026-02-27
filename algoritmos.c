#include <stdio.h>
#include <stdlib.h>

/* ########## Backtracking ##########*/

void backtracking(int k, int n, int T, int t[], int p[], int T_actual, int p_actual, int* p_max, int seleccion_actual[], int mejor_seleccion[]){
    //poda al pasarse del tiempo
    if(T_actual > T){
        return;
    }

    //caso base
    if(k == n){
        if(p_actual > *p_max){
            *p_max = p_actual;
            
            for (int i = 0; i < n; i++){
                mejor_seleccion[i] = seleccion_actual[i];
            }
        }
        return;
    }

    //desición de estudiar o no el tema k

    //no estudiar el tema k
    seleccion_actual[k] = 0;
    backtracking(k + 1, n, T, t, p, T_actual, p_actual, p_max, seleccion_actual, mejor_seleccion);

    //sí estudiar el tema k
    seleccion_actual[k] = 1;
    backtracking(k + 1, n, T, t, p, T_actual + t[k], p_actual + p[k], p_max, seleccion_actual, mejor_seleccion);
}

//función de inicialización, pide el arreglo de mejor selección ya que la función solo rellena los datos,
//pero estos se guardan fuera
int maximizar_puntaje_backtracking(int n, int T, int t[], int p[], int mejor_seleccion[]){
    int* seleccion_actual = (int*)malloc(n*sizeof(int));

    for (int i = 0; i < n; i++){
        seleccion_actual[i] = 0;
        mejor_seleccion[i] = 0;
    }

    int p_max = 0;

    backtracking(0, n, T, t, p, 0, 0, &p_max, seleccion_actual, mejor_seleccion);

    free(seleccion_actual);
    return p_max;
}

/* ########## Goloso ##########*/

/* ########## Dinámico ##########*/