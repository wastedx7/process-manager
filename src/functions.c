#include "main.h"

// to read all cpu stats and return the time in jiffies
void read_cpu_stats(CPUStats *s){
    FILE *fp = fopen("/proc/stat", "r");
    if(!fp){
        perror("could not open /proc/stat");
        return;
    }
    // user, nice, system, idle, iowait, irq, softirq, steal;
    char label[10];
    fscanf(fp, "%s %llu %llu %llu %llu %llu %llu %llu",
           label, &s->user, &s->nice, &s->system, &s->idle, &s->iowait, &s->irq, &s->softirq, &s->steal);

    s->total = s->user + s->nice + s->system + s->idle + s->iowait + s->irq + s->softirq + s->steal;

    fclose(fp);
}

// 
int read_processes_stats(Process *list){
    char path[256], buff[1024];
    snprintf(path, sizeof(path), "/proc/%d/stat", list->pid);

    FILE *f = fopen(path, "r");
    if (!f) return -1;

    if (!fgets(buff, sizeof(buff), f)){
        fclose(f);
        return -1;
    }

    fclose(f);

    char com[256];  // variable to store the command
    char state;     // variable to store the state of a process

    sscanf(buff, "%d (%[^)]) %c", &list->pid, com, &state);
    my_strcpy(com, list->name);     // copy name into com

    char* ptr = buff;   // pointer to a char to buff
    int field;          // field counter in buff

    while(field < 14 && *ptr){
        if(*ptr == ' ') field++;
        ptr++;
    }

    sscanf(buff, "%lu %lu", list->utime, list->stime);  // read from buff and store the utime and stime
    return 0;
}