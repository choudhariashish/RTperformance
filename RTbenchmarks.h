/*
 * RTbenchmarks.h
 *
 *  Created on: Nov 8, 2012
 *      Author: ashish
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#ifndef RTBENCHMARKS_H_
#define RTBENCHMARKS_H_

using namespace std;

//declaring available functions
#define AvailableFunctions	5
void binary_search(void);
void jfdctint(void);
void matmult(void);
void sqrtfcn(void);
void lmsfcn(void);

class TASK
{
public:
	void (*funcPtr)(void);
	int TaskID;
};

struct RTTASKDATA
{
	int TASK_ID;
	int TASK_PRIORITY;
	long TASK_PERIOD;
	int TASK_COUNT;
	void (*TASK_FUNCTION)(void);
};

void initializeAllTasks(TASK* Task);
void printAvailableTasks();
void calculateWcet(vector<int>* WcetIDs, TASK* Task, int count, bool rtFlag);
void forkFunctionsAsRTTasks(void (*funcPtr)(void), int count);
void *forkForWcet(void *data);
void *forkForWcetNonRT(void *data);

#endif /* RTBENCHMARKS_H_ */
