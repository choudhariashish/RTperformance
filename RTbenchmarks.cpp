/*
 * RTbanchmarks.cpp
 *
 *  Created on: Nov 12, 2012
 *      Author: ashish
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "RTbenchmarks.h"

//void (*funcArr[])(void) = {binary_search, jfdctint, matmult, sqrtfcn, lmsfcn};
//= {binary_search, jfdctint, matmult, sqrtfcn, lmsfcn};

void initializeAllTasks(TASK* Task)
{
	Task[0].TaskID = 1;
	Task[0].funcPtr = binary_search;

 	Task[1].TaskID = 2;
	Task[1].funcPtr = jfdctint;

	Task[2].TaskID = 3;
	Task[2].funcPtr = matmult;

	Task[3].TaskID = 4;
	Task[3].funcPtr = sqrtfcn;

	Task[4].TaskID = 5;
	Task[4].funcPtr = lmsfcn;

}

void printAvailableTasks(void)
{
	cout << "\n"<<endl;
	cout << "TASK NAME    "<<"\t\t"<<"ID\n"<<endl;

	cout << "binary_search"<<"\t\t"<<"1"<<endl;
	cout << "jfdctint     "<<"\t\t"<<"2"<<endl;
	cout << "matmult      "<<"\t\t"<<"3"<<endl;
	cout << "sqrt         "<<"\t\t"<<"4"<<endl;
	cout << "lms          "<<"\t\t"<<"5"<<endl;
	cout << "\n"<<endl;
}

void calculateWcet(vector<int>* WcetIDs, TASK* Task, int count, bool rtFlag)
{
	int fit;
	unsigned int wit;
	pthread_t RTTfunctionThread[WcetIDs->size()];

	int p = 45;

	for(wit = 0; wit < WcetIDs->size(); wit++)
	{
		for(fit = 0; fit < AvailableFunctions; fit++)
		{
			if( Task[fit].TaskID == WcetIDs->at(wit) )
			{
				RTTASKDATA *TaskData = new RTTASKDATA;
				cout <<"\nforking task "<<Task[fit].TaskID;
				TaskData->TASK_COUNT = count;
				TaskData->TASK_FUNCTION = Task[fit].funcPtr;
				TaskData->TASK_PERIOD = 1000000;
				TaskData->TASK_PRIORITY = p;
				TaskData->TASK_ID = Task[fit].TaskID;
				cout<<"\np-> "<<p;
				p--;
				if(rtFlag==1)
					pthread_create(&RTTfunctionThread[Task[fit].TaskID], NULL, forkForWcet, (void *)TaskData);
				else
					pthread_create(&RTTfunctionThread[Task[fit].TaskID], NULL, forkForWcetNonRT, (void *)TaskData);
			}
		}
	}

	for(wit = 0; wit < WcetIDs->size(); wit++)
	{
		for(fit = 0; fit < AvailableFunctions; fit++)
		{
			if( Task[fit].TaskID == WcetIDs->at(wit) )
			{
                pthread_join(RTTfunctionThread[Task[fit].TaskID], NULL);

			}
		}
	}
}

void forkFunctionsAsRTTasks(void (*funcPtr)(void), int count)
{

//	forkForWcet(funcPtr, count);
}
