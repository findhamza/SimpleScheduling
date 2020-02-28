/* Author:	Hamza Syed	*/
/* COSC4317:	Compilers	*/
/* Part-1:	Lexical		*/

//Include Sector
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


//Struct Sector
typedef struct {
	int arr[100][3];
	int mCycle;
} arr2d;


//Function Declaration Sector
arr2d getTaskInfo(char*);
void startCPU(arr2d);

int main()
{
	char *fileName = malloc(256);

	printf(":::Preemtive Priority Scheduler:::\n\n");
	printf("Please enter file name: ");

	scanf("%255s", fileName);
	printf("\nFile is: %s\n\n", fileName);

	arr2d p_stack = getTaskInfo(fileName);

	for(int i=0; i<100; i++)
		printf("Arrival: %d\tPriority: %d\tTime: %d\n",
			p_stack.arr[i][0], p_stack.arr[i][1], p_stack.arr[i][2]);

	printf("Total Cycles: %d", p_stack.mCycle);
	startCPU(p_stack);

	return 0;
}

arr2d getTaskInfo(char *fileName)
{
	FILE *file = fopen(fileName, "r");
	int num=0, r=0, c=0;
	arr2d info;
	info.mCycle = 0;

	fscanf(file, "%d", &num);

	while(!feof(file))
	{
		fscanf(file, "%d", &num);
		printf("\n%d", num);
		info.arr[r][c] = num;
		if(c==2){info.mCycle+=info.arr[r][c];}
		printf("Total Cycles: %d", info.mCycle);
		c++;

		if(c>=3){c=0; r++;}
		if(r>=100){printf("ARRAY SMASHED"); exit(0);}
	}

	c=0;
	for(int i=r; i<100; i++)
	{
		info.arr[i][c] = 0;
		info.arr[i][c+1] = 0;
		info.arr[i][c+2] = 0;
	}

	fclose(file);
	return info;
}

void startCPU(arr2d pStack)
{
	for(int cycle=0; cycle<pStack.mCycle; cycle++)
	{
		

	}
}
