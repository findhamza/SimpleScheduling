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
	int next;
} arr2d;


//Function Declaration Sector
arr2d getTaskInfo(char*);
void startCPU(arr2d);
int nextProcess(arr2d, int);
int same(const int[], int);

//Global Declaration
#define DONE 999

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

	printf("Total Cycles: %d\n\n", p_stack.mCycle);
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
		printf("Total Cycles: %d\n\n", info.mCycle);
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
	pStack.next=0;
	int robin = 3;
	int robinCur = 0;
	int rr[3];


	for(int cycle=0; cycle<pStack.mCycle; cycle++)
	{
		pStack.next = nextProcess(pStack, cycle);

		if(same(rr,robin))
		{
//			pStack.next++;
			pStack.next = nextProcess(pStack, cycle);
		}

		pStack.arr[pStack.next][2]--;
		if(pStack.arr[pStack.next][2]<=0)
			pStack.arr[pStack.next][1] = DONE;

		rr[robinCur] = pStack.next;
		robinCur++;
		if(robinCur>=robin){robinCur=0;}

//		printf("%d :: %d\n",rr[0],rr[1]);

		printf("Cycle: %d\tProcess: %d\tRemaining: %d\n", cycle, pStack.next, pStack.arr[pStack.next][2]);
	}
}

int nextProcess(arr2d pStack, int cycle)
{
	int next = pStack.next;

	for(int i=0; i<cycle; i++)
	{
		if(pStack.arr[i][2]>0 && pStack.arr[i][0]<=cycle)
			if(pStack.arr[i][1]<pStack.arr[next][1])
				next = i;
			else
				continue;
	}

	return next;
}

int same(const int a[], int n)
{
	while(--n>0 && a[n]==a[0]);
	return n!=0;
}
