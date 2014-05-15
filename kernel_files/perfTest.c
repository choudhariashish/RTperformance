#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include "perfMonIOCTL18.h"
#include "e500mc_events.h"

#define numberOfEvents		4

#define length			24*8192

int eventArray[numberOfEvents] = {DATA_L1_CACHE_RELOADS,
				  DATA_L1_CACHE_CASTOUTS,
				  L2_CACHE_DATA_ACCESSES,
				  L2_CACHE_DATA_HITS};

int myrand(void);
static unsigned long next = 1;
FILE *outFile;
int pmcCounterL1ReloadsValue[numberOfEvents];

int main(int argc, char *argv[])
{
char *file_name = "/dev/perfMon";

int begin = 0;
int a[length], b[length];

int count = 0;
int fd;
int i = 0;
int ctr = 0;
if((outFile = fopen(argv[1], "a")) == NULL){
printf("Error opening data file \n");
exit(0);
}
unsigned long pmcCounterL1Reloads;
system("insmod /home/hyper/kernelModuleCheck/files/perfMonIOCTL18.ko");
fd = open(file_name, O_RDWR);
if (fd == -1)
{
perror("query_apps open");
return 2;
}

for(count = 0; count < numberOfEvents; ++count){
int event;
if((event = ioctl(fd, PERF_MON_EVENT_OPEN, eventArray[count])) == -1){
perror("perf_mon_event_open error");
exit(0);
}
//printf("Event mapped to counter %d\n", event);
if(ioctl(fd, PERF_MON_RESET, count) == -1){
perror("perf_mon_reset error");
}
}


for(count = 0; count < numberOfEvents; count++){
if(ioctl(fd, PERF_MON_ENABLE, count) == -1){
perror("perf_mon_reset error");
}
}

// This is the piece of code for which the performance monitoring is done.

for(begin = 0; begin < length; begin++){
a[begin] = begin;
}
for(begin = 0; begin < length; begin++){
int k=0;
int j = 0;
for(j = 0; j < 100; ++j)
k = (k + myrand()) % length;
b[begin] = a[k];
}

for(begin = 0; begin < length; begin++){
int k=0;
int j = 0;
for(j = 0; j < 100; ++j)
k = (k + myrand()) % length;
a[begin] =b[k];
}

for(count = 0; count < numberOfEvents; ++count){
if(ioctl(fd, PERF_MON_DISABLE, count) == -1){
perror("perf_mon_disable error");
}
}
for(count = 0; count < numberOfEvents; count++){
if((pmcCounterL1ReloadsValue[count] = ioctl(fd, PERF_MON_READ, count)) == -1){
perror("perf_mon_read error");
}
//printf("Counter %d value is %lu\n", count, pmcCounterL1ReloadsValue[count]);
}
fprintf(outFile, "L1_data_reloads %lu \n",pmcCounterL1ReloadsValue[0]);
fprintf(outFile, "L1_data_castouts %lu \n",pmcCounterL1ReloadsValue[1]);
fprintf(outFile, "L2_data_cache_accesses %lu \n", pmcCounterL1ReloadsValue[2]);
fprintf(outFile, "L2_data_hits %lu \n", pmcCounterL1ReloadsValue[3]);
close (fd);
system("rmmod /home/hyper/kernelModuleCheck/files/perfMonIOCTL18.ko");
return 0;
}

int myrand(void) {
next = next * 1103515245 + 12345;
return((unsigned)(next/65536) % 32768);
}
