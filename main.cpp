/*
 * main.cpp
 *
 *  Created on: Nov 8, 2012
 *      Author: ashish
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <typeinfo>

#include "RTbenchmarks.h"

//#define debug

using namespace std;

int main(int argc, char* argv[])
{
	int i = 1, tempID, count=0;
	bool rtFlag = false;
	int num_of_tasks, taskIter=0;
	vector<int> WcetIDs;
	TASK Task[AvailableFunctions];

	if(argc<2)
	{
		cout<<"\nNot enough arguments\nUsage:./RTbenchmarks -c 10 -r 1 -w 1,2\n";
		return -1;
	}
	//Initialize All Tasks
	cout <<"\n*************************************"<<endl;
	cout <<  "INITIALIZING ALL TASKS......";
	initializeAllTasks(Task);
	cout<<"done..!"<<endl;
	for( i = 0; i < argc; i++ )
	{
		if( argv[i][0] == '-' )
		{
			switch((char)argv[i][1])
			{
			case 'c':
				count = atoi(argv[++i]);
			break;
			case 'r':
				rtFlag = 1;
			break;
			case 'w':
				cout << "\nFollowing TASK WCET'S will be calculated*******"<<endl;
				num_of_tasks = atoi(argv[++i]);
				WcetIDs.resize(num_of_tasks);
				cout << "Total Number of TASKS = "<<num_of_tasks<<"\nWCET TaskIDs: ";
				while(taskIter < num_of_tasks)
				{
					tempID = atoi(argv[++i]);
					if(tempID>AvailableFunctions)
					{
						cerr<<"\n\n!!!...Task ID-> "<<tempID<<" invalid...!!!\ncannot continue..!\n\n";
						return 1;
					}

					WcetIDs[taskIter] = tempID;
					cout << tempID<<" ";
					taskIter++;
				}
				if(count>0)
				{
					cout << "\n\nCalculating WCET'S .........";
					calculateWcet(&WcetIDs, Task, count, rtFlag);
					cout<<"\ndone..!\n"<<endl;
				}
				else
				{
					cerr<<"\n\n!!!...count->invalid..should be >=1"
							"\neg: usage: ./RTbenchmarks -c 1\ncannot continue..!\n\n";
					return 1;
				}
			break;

			case 'l':
				cout << "Following TASK'S are available************"<<endl;
				printAvailableTasks();
			break;


			default: {cout<<"Invalid arguments"<<endl;}break;
			}
		}
	}
#ifdef debug
	unsigned int size = 0;
	while(size < WcetIDs.size())
	{
		cout << "\nTASK-ID = "<< WcetIDs[size]<<endl;
		size++;
	}
#endif

//	for(int i = 0; i < 10; i++)
//	{
//		binary_search(8);
//		jfdctint();
//		matmult();
//		cout << "\n sqrtfcn(25) :"<< sqrtfcn(25)<<endl;
//		lms();
//	}

	return 0;
}
