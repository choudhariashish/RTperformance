/*
 * wcetCalculator.cpp
 *
 *  Created on: Nov 14, 2012
 *      Author: ashish
 */
#include "RTbenchmarks.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/perf_event.h>
#include <asm/unistd.h>

#include <time.h>
#include <sched.h>
#include <sys/mman.h>
#include <string.h>

/*------------Performance counter open-----------------*/
long perf_event_open( struct perf_event_attr *hw_event, pid_t pid,
                      int cpu, int group_fd, unsigned long flags )
{
    int ret;
    ret = syscall( __NR_perf_event_open, hw_event, pid, cpu,
                   group_fd, flags );
    return ret;
}
/*------------Performance counter open-----------------*/


//#define MY_PRIORITY (49) /* we use 49 as the PRREMPT_RT use 50
//                            as the priority of kernel tasklets
//                            and interrupt handler by default */

//int MY_PRIORITY = 49;

#define MAX_SAFE_STACK   8*1024		 /* The maximum stack size which is
                                   guaranteed safe to access without
                                   faulting */

#define NSEC_PER_SEC    (1000000000) /* The number of nsecs per sec. */


void stack_prefault(void) {

        unsigned char dummy[MAX_SAFE_STACK];

        memset(dummy, 0, MAX_SAFE_STACK);
        return;
}

void *forkForWcet(void *data)
{

		struct timespec t, OBSERVE_EXEC1, OBSERVE_EXEC2;
		struct sched_param param;

		RTTASKDATA *TaskData = (RTTASKDATA*)data;

		int interval = TaskData->TASK_PERIOD;
		int MY_PRIORITY = TaskData->TASK_PRIORITY;
		param.sched_priority = MY_PRIORITY;

		cout<<"\n\nMY_PRIORITY-"<<MY_PRIORITY<<" MY_PERIOD-"<<TaskData->TASK_PERIOD<<endl;

//        struct timespec t;
//        struct sched_param param;
//      int interval = 50000; /* 50us*/
        /* Declare ourself as a real time task */
//        param.sched_priority = MY_PRIORITY;

		if(sched_setscheduler(0, SCHED_RR, &param) == -1) {
                perror("sched_setscheduler failed");
                exit(-1);
        }

        /* Lock memory */

        if(mlockall(MCL_CURRENT|MCL_FUTURE) == -1) {
                perror("mlockall failed");
                exit(-2);
        }

        /* Pre-fault our stack */

        stack_prefault();

        clock_gettime(CLOCK_MONOTONIC ,&t);
        /* start after one second */
        t.tv_sec++;
        int it=0;
        int tempCount=0;

        /*------------Performance-------------------*/
    	//for cache miss
        struct perf_event_attr pe;
        long long count;
        int fd;
        memset(&pe, 0, sizeof(struct perf_event_attr));
        pe.type = PERF_TYPE_HW_CACHE ;
        pe.size = sizeof(struct perf_event_attr);
        pe.config=(PERF_COUNT_HW_CACHE_L1D )|(PERF_COUNT_HW_CACHE_OP_WRITE  << 8)|(PERF_COUNT_HW_CACHE_RESULT_MISS << 16);
        pe.disabled = 1;
        pe.exclude_kernel = 1;
        pe.exclude_hv = 1;
        fd = perf_event_open(&pe, 0, -1, -1, 0);
        if (fd < 0) {
           fprintf(stderr, "Error opening leader %llx\n", pe.config);
        }
        /*------------Performance END-------------------*/
        /*------------Performance Start counter-------------------*/
        ioctl(fd, PERF_EVENT_IOC_RESET, 0);
        ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
        /*------------Performance Start counter-------------------*/

        while(1)
        {
        		if(tempCount == TaskData->TASK_COUNT)
        			break;

                /* wait until next shot */
                clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
                clock_gettime(CLOCK_MONOTONIC ,&OBSERVE_EXEC1);

                /* do the stuff */
//                for(it=0;it<100;it++)
                TaskData->TASK_FUNCTION();

                clock_gettime(CLOCK_MONOTONIC ,&OBSERVE_EXEC2);
                cout<<"\nEXEC TIME OBSERVED: "<<OBSERVE_EXEC2.tv_nsec-OBSERVE_EXEC1.tv_nsec
                		<<" TaskID: "<<TaskData->TASK_ID
                		<<" TaskPERIOD: "<<TaskData->TASK_PERIOD
                		<<" TaskPRIORITY: "<<TaskData->TASK_PRIORITY<<endl;

				/* calculate next shot */
                t.tv_nsec += interval;

                while (t.tv_nsec >= NSEC_PER_SEC) {
                       t.tv_nsec -= NSEC_PER_SEC;
                        t.tv_sec++;
                }
                tempCount++;
        }

        /*------------Performance END counter-------------------*/
        ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
        read(fd, &count, sizeof(long long));
        printf("Had %lld L1 D-cache-misses\n", count);
        close(fd);
        /*------------Performance END counter-------------------*/

        pthread_exit(NULL);
}

void *forkForWcetNonRT(void *data)
{

		struct timespec t, OBSERVE_EXEC1, OBSERVE_EXEC2;

		RTTASKDATA *TaskData = (RTTASKDATA*)data;

		int interval = TaskData->TASK_PERIOD;

		cout<<"\nMY_PERIOD-"<<TaskData->TASK_PERIOD<<" ";

        /* Lock memory */

        if(mlockall(MCL_CURRENT|MCL_FUTURE) == -1) {
                perror("mlockall failed");
                exit(-2);
        }

        /* Pre-fault our stack */
        stack_prefault();

        clock_gettime(CLOCK_MONOTONIC ,&t);
        /* start after one second */
        t.tv_sec++;


        int tempCount=0;
        while(1)
        {

        		if(tempCount == TaskData->TASK_COUNT)
        			break;

                /* wait until next shot */
                clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);

                clock_gettime(CLOCK_MONOTONIC ,&OBSERVE_EXEC1);

                /* do the stuff */
                TaskData->TASK_FUNCTION();

                clock_gettime(CLOCK_MONOTONIC ,&OBSERVE_EXEC2);
                cout<<"\nEXEC TIME OBSERVED: "<<OBSERVE_EXEC2.tv_nsec-OBSERVE_EXEC1.tv_nsec
                		<<" TaskID: "<<TaskData->TASK_ID<<endl;

				/* calculate next shot */
                t.tv_nsec += interval;

                while (t.tv_nsec >= NSEC_PER_SEC) {
                       t.tv_nsec -= NSEC_PER_SEC;
                        t.tv_sec++;
                }
                tempCount++;

        }
        pthread_exit(NULL);
}

