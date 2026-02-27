#include <stdio.h>
#include <stdlib.h>

//The Greedy Algorithm
void HungerForTasks(int n, double time[], double score[], int T){
	/*Considering a set of tasks numbered from 1 to n. Each task has its own time and score, which share the same index. 
	Example: Task number x (element x-1 from a "tasks[]" array) is related to the elements from time[x-1] and score[x-1], 
	We'll re-sort the tasks and their arrays according to a ratio calculation. The ratio of a task will be calculated as (task_score / task_time). */
	
	int* tasks = (int*)malloc(n*sizeof(int)); //The array for each numbered task.
	double* task_ratio = (double*)malloc(n*sizeof(double)); //The array for each task's ratio. The ratio of two integers may result into a decimal number, which is supported by a "double" variable.
	int* selected = (int*)malloc(n*sizeof(int)); //Array which will later store the selected tasks for the Greedy Algorithm.
	
	for (int i=0;i<n;i++){
		tasks[i] = i+1; //Task indexes from 1 to n
		task_ratio[i] = score[i]/time[i]; //Ratio for a specific task
		selected[i] = -1; //Initializing the "selected" array
	}
	//Now, we'll replace each task index choosing from the highest ratio to the lowest
	int i = 0;
	while (i+1 < n){ //Swapping based on Bubble Sorting
		int i2 = i+1;
		int sorted = 0; //In this variable, 0 means "false" while 1 means "true" 	
		while (i2 < n){
			if (task_ratio[i] < task_ratio[i2]){
				int temp1;
				double temp2, temp3, temp4;
				//Swap for elements from the "tasks" array
				temp1 = tasks[i];
				tasks[i] = tasks[i2];
				tasks[i2] = temp1;
				//Swap for elements from the "task_ratio" array
				temp2 = task_ratio[i];
				task_ratio[i] = task_ratio[i2];
				task_ratio[i2] = temp2;
				//Swap for elements from the  "score" array
				temp3 = score[i];
				score[i] = score[i2];
				score[i2] = temp3;
				//Swap for elements from the "time" array
				temp4 = time[i];
				time[i] = time[i2];
				time[i2] = temp4;
				//"sorted" flag will mean "true" now.
				sorted = 1;
				}
			i2+=1;
			}
		if (sorted == 0){ //If the flag hasn't changed, the loop will have a break.
			break;
		}
		i += 1;
		}
	int TotalTime=0, TotalScore=0, k=-1;
	for (int j=0;j<n;j++){
		if (TotalTime + time[j] <= T){ //If the acumulated time doesn't outdo the T variable, then we select a task
			TotalTime+=time[j]; //Total Time increases
			TotalScore+=score[j]; //Total Score increases
			k+=1;//We move the k index for our "selected" array.
			selected[k] = tasks[j]; //A selected task is now stored in the array.
			}
	}
	printf("The final score from the tasks is %d. \n",TotalScore);
	printf("The selected tasks were: \n");
	for (int k=0;k<n;k++){
		if (selected[k] != -1){
			printf("%d \n", selected[k]);
			}
		}
	printf("End of Greedy Algorithm \n");	
	return;
}
//The Execution Algorithm
int main(int argc, char* argv[]){
	int n, T;
	
	FILE* time_archive = fopen(argv[1], "r");
	FILE* score_archive = fopen(argv[2], "r");

	fscanf(time_archive, "%d", &T); //Obtaining Maximum Time "T"
	fscanf(time_archive, "%d", &n); //Obtaining total amount of tasks "n"
	/*NOTE: The main is reading two txt archives. The first archive shows the Maximum Time (first line), 
	then the amount of tasks (second line) and finally the time value of each task (rest of lines).
	The second archive stores the score value of each task.
	
	Example:
	1) time.txt content:
	line 1: 50
	line 2: 5
	line 3: 32
	line 4: 12
	line 5: 21
	line 6: 5
	line 7: 17
	2) score.txt content:
	line 1: 30
	line 2: 21
	line 3: 67
	line 4: 32
	line 5: 11
	*/
	
	double* time = (double*)malloc(n*sizeof(double)); // "time" elements will be positive integers
	double* score = (double*)malloc(n*sizeof(double)); //"score" elements will be positive integers
	
	for (int i = 0;i<n;i++){
		int number1, number2;
		fscanf(time_archive, "%d", &number1); //array with positive integers
		fscanf(score_archive, "%d", &number2); //array with positive integers
		time[i] = number1;
		score[i] = number2;
		}
	//We filled our time and score arrays
	HungerForTasks(n, time, score, T);
	return 0;
	}