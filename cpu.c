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
	int pTime[100];
	int quant;
} arr2d;


//Function Declaration Sector
arr2d getTaskInfo(char*);
void startCPU(arr2d);
int nextProcess(arr2d, int, bool);
int same(const int[], int);
void turnAround(arr2d);

//Global Declaration
#define DONE 999

int main()
{
	char *fileName = malloc(256);
	int quantum = 0;

	printf(":::Preemtive Priority Scheduler:::\n\n");
	printf("Please enter file name: ");

	scanf("%255s", fileName);
	printf("Please enter Quantum: ");
	scanf("%d", &quantum);

	printf("\nFile is: %s\n", fileName);
	printf("Quantum: %d\n\n", quantum);

	arr2d p_stack = getTaskInfo(fileName);
	p_stack.quant = quantum;

	for(int i=0; i<100; i++)
		if(p_stack.arr[i][2]!=0)
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
//		printf("\n%d", num);
		info.arr[r][c] = num;
		if(c==2){info.mCycle+=info.arr[r][c];}
//		printf("Total Cycles: %d\n\n", info.mCycle);
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
	int robin = pStack.quant;
	int robinCur = 0;
	int rr[robin];
	bool flop=false;


	for(int cycle=0; cycle<pStack.mCycle; cycle++)
	{
		rr[robinCur] = pStack.next;


		pStack.next = nextProcess(pStack, cycle, true);//flop);

		if(pStack.arr[pStack.next][1] == pStack.arr[rr[robinCur]][1] && robinCur!=0)
		{
			if(pStack.arr[rr[robinCur]][2]>0)
			{
//				pStack.next = rr[robinCur];
				pStack.next = nextProcess(pStack, cycle, false);
//				printf("No Switch\n");
				robinCur = -1;
			}
		}
		else
		{
			pStack.next = 0;
			pStack.next = nextProcess(pStack, cycle, true);//true);
//			printf("Swtich\n");
		}

		pStack.arr[pStack.next][2]--;
		if(pStack.arr[pStack.next][2]<=0)
		{
			pStack.arr[pStack.next][1] = DONE;

			pStack.pTime[pStack.next] = cycle-pStack.arr[pStack.next][0];
		}

		robinCur++;
		if(robinCur>=robin){robinCur=0;}
//		if(same(rr,robin)!=0){flop=false;}

//		printf("%d :: %d\n",rr[0],rr[1]);

		printf("Cycle: %d\tProcess: %d\tRemaining: %d\tFlop: %d\n", cycle, pStack.next, pStack.arr[pStack.next][2], flop);
	}

	turnAround(pStack);
}

int nextProcess(arr2d pStack, int cycle, bool flop)
{
	int next = pStack.next;
	int index;

	for(int i=0; i<cycle; i++)
	{
		if(flop)
			index = (i + next) % cycle;
		if(!flop)
			index = i;

		if(pStack.arr[index][2]>0 && pStack.arr[index][0]<=cycle)
			if(pStack.arr[index][1]<=pStack.arr[next][1])
			{
				next = index;
			}
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

void turnAround(arr2d pStack)
{
	printf("\nTurnaround Time\n");

	float avg = 0;

	for(int i=0; i<100; i++)
		if(pStack.arr[i][0] == pStack.arr[i][1] == pStack.arr[i][2] != 0)
		{
			printf("Process[%d]: %d\n", i, pStack.pTime[i]);
			avg+=pStack.pTime[i];
		}
		else
		{
			avg/=i--;
			break;
		}

	printf("\nAverage: %lf\n\n",avg);
}
