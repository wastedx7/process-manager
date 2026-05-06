// HEADERS !!
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>

// DATA STRUCTURES
// basic structure for all processes 
typedef struct {
    int pid;
    char name[1024];
    unsigned long utime, stime;
    unsigned long total_time;
    long memory; // VmRss (amount of process mem in ram)
    float cpu;
} Process; 

// for read_stats
typedef struct {
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
    unsigned long long total;
} CPUStats;

// FUNCTIONS AND IMPLEMENTATIONS
void read_cpu_stats(CPUStats *s);
int read_processes_stats(Process *list);

// HELPER FUNCTIONS 
int is_numeric(const char *s);
char* my_strcpy(char* dest, const char* src);