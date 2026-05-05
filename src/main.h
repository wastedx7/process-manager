#include <stdio.h>
#include <unistd.h>

// basic structure 
typedef struct {
    int pid;
    char name[1024];
    unsigned long utime, stime;
    unsigned long total_time;
    long memory; // VmRss (amount of process mem in ram)
    float cpu;
} Process; 

typedef struct {
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
    unsigned long long total;
} CPUStats;

void read_stats(CPUStats *s);
// unsigned long long get_total_cpu_time();