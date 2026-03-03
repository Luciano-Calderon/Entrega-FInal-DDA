#include <stdio.h>
#include <stdlib.h>

extern long long iteraciones_bt;
extern long long iteraciones_goloso;
extern long long iteraciones_dp;

/* ########## Backtracking ########## */

void backtracking(int k, int n, int T, int t[], int p[], int T_actual, int p_actual, int* p_max, int seleccion_actual[], int mejor_seleccion[]){
	iteraciones_bt++;

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

/* ########## Goloso ########## */

//El Algoritmo Goloso
int Greedy(int n, int T, int tiempo[], int puntaje[], int mejor_seleccion[]){
	
	double* clon_tiempo = (double*)malloc(n*sizeof(double)); //Clonando arreglo de tiempo, para no alterar su arreglo original
	double* clon_puntaje = (double*)malloc(n*sizeof(double)); //Clonando arreglo de puntaje
	int* tareas = (int*)malloc(n*sizeof(int)); //Arreglo con las tareas ennumeradas
	double* razon_tareas = (double*)malloc(n*sizeof(double)); //Arreglo que guardará la razon entre el puntaje y tiempo de cada tarea (puntaje_de_tarea/tiempo_de_tarea)
	
	for (int i=0;i<n;i++){
		clon_puntaje[i] = puntaje[i];
		clon_tiempo[i] = tiempo[i];
		tareas[i] = i+1; //índices de tareas
		razon_tareas[i] = puntaje[i]/tiempo[i]; //Razón de cada tarea
		mejor_seleccion[i] = -1; //Inicializando el arreglo de selección, consecuentemente el arreglo guardará las tareas que generan el mejor puntaje
	}
	//Ahora, se ordenarán las tareas, sus tiempos y sus puntajes según los valores de cada razón (posicionando valores de mayor a menor)
	int i = 0;
	while (i+1 < n){ //Intercambio basado en el método de Bubble Sort
		int i2 = i+1;
		int sorted = 0; //En esta variable, 0 significa "falso" y 1 significa "verdadero"
		while (i2 < n){
			iteraciones_goloso++;

			if (razon_tareas[i] < razon_tareas[i2]){ //si la razón de una tarea es menor que la razón de una tarea sucesora, cambiamos las posiciones.
				int temp1;
				double temp2, temp3, temp4;
				//Cambiando elementos del arreglo de tareas
				temp1 = tareas[i];
				tareas[i] = tareas[i2];
				tareas[i2] = temp1;
				//Cambiando elementos del arreglo de razones
				temp2 = razon_tareas[i];
				razon_tareas[i] = razon_tareas[i2];
				razon_tareas[i2] = temp2;
				//Cambiando elementos del arreglo de puntajes
				temp3 = clon_puntaje[i];
				clon_puntaje[i] = clon_puntaje[i2];
				clon_puntaje[i2] = temp3;
				//Cambiando elementos del arreglo de tiempos
				temp4 = clon_tiempo[i];
				clon_tiempo[i] = clon_tiempo[i2];
				clon_tiempo[i2] = temp4;
				//"sorted" será verdadero ahora
				sorted = 1;
				}
			i2+=1;
			}
		if (sorted == 0){ //Si la bandera no ha cambiado, habrá un break
			break;
		}
		i += 1;
		}
	int TiempoTotal=0, PuntajeTotal=0, k=-1;
	for (int j=0;j<n;j++){
		iteraciones_goloso++;

		if (TiempoTotal + clon_tiempo[j] <= T){ //Si el tiempo acumulado no supera al tiempo máximo T, entonces aumentamos tiempo y puntaje acumulado, así como seleccionamos una tarea
			TiempoTotal+=clon_tiempo[j];
			PuntajeTotal+=clon_puntaje[j];
			k+=1;//Movemos el índice k para el arreglo de seleccionados
			mejor_seleccion[k] = tareas[j]; //Tarea seleccionada y guardada
			}
	}

	/*
	printf("Algoritmo Goloso: \nEl puntaje maximizado resultó en %d. \n",PuntajeTotal);
	printf("Las tareas seleccionadas fueron: \n");
	for (int k=0;k<n;k++){
		if (mejor_seleccion[k] != -1){
			printf("%d ", mejor_seleccion[k]);
			}
		}
		printf("\n");
	printf("Fin de Algoritmo Goloso \n");
	*/

	free(tareas);
	free(razon_tareas);
	free(clon_tiempo);
	free(clon_puntaje);

	return PuntajeTotal;
}

/* ########## Dinámico ##########*/

int DynamicProgramming(int n, int T, int* time, int* score, int* mejor_seleccion){
	//Se crea matríz DP, de tamaño (n+1)x(T+1)
	int** DP = (int**)malloc((n+1)*sizeof(int*)); //n+1 filas
	for (int i=0;i<=(n);i++){
		DP[i] = (int*)malloc((T+1)*sizeof(int)); //Cada fila tendrá (T+1) columnas
		for (int j=0;j<=(T);j++){
			DP[i][j] = 0; //Inicializando cada elemento de la Matríz en 0
		}
	}
	//Estudiar cada tarea
	for (int i=1;i<=n;i++){
		for(int j=0;j<=T;j++){
			iteraciones_dp++;

			DP[i][j] = DP[i-1][j]; //Clonando valor acumulado de la fila anterior
			//Evaluar uso de tarea i
			if (time[i-1] <= j){ //si el tiempo en revisión corresponde al nivel de la columna revisada (las columnas representan niveles de tiempo usado)
				int elemento = DP[i-1][j-time[i-1]] + score[i-1]; //Valor entre acumulador anterior y puntaje en revisión
				if (elemento > DP[i][j]){ //Si el puntaje acumulado resulta mayor.
					DP[i][j] = elemento; //actualizamos casilla
					}
				}
		}
	}
	int puntaje_final = DP[n][T];

	for (int i=0;i<n;i++){
		mejor_seleccion[i] = -1; //Inicializando el arreglo de selección, consecuentemente el arreglo guardará las tareas que generan el mejor puntaje
	}
	int j_aux = T, k = 0;
    for(int i=n; i>=1; i--){
        if (DP[i][j_aux] != DP[i-1][j_aux]){
            mejor_seleccion[k++] = i; // Guardamos el índice de la tarea
            j_aux = j_aux - time[i-1];
        }
    }

	/*
	printf("Las tareas seleccionadas por DP fueron: \n");
	for(int i=0;i<n;i++){
		if (mejor_seleccion[i] != -1){
			printf("%d ", mejor_seleccion[i]);
			}
		}
		printf("\n");
	printf("Fin de Algoritmo de Programación Dinámica. \n");
	*/

	for(int i=0;i<=n;i++){ //bucle que va de 0 a n, para el arreglo DP que contiene n+1 filas
		free(DP[i]); //se liberan filas de DP
		}
	free(DP);//Se libera el arreglo global de DP

	return puntaje_final;
	}