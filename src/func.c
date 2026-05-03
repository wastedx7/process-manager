#include "procmon.h"

void read_stats(CPUStats *s){
    FILE *fp = fopen("/proc/stat", "r");
    if(!fp){
        perror("could not open /proc/stat");
        return;
    }
    // user, nice, system, idle, iowait, irq, softirq, steal;
    char label[10];
    fscanf(fp, "%s %llu %llu %llu %llu %llu %llu %llu", label,
    &s->user, &s->nice, &s->system, &s->idle, &s->iowait, &s->irq, &s->softirq, &s->steal);

    s->total = s->user + s->nice + s->system + s->idle + s->iowait + s->irq + s->softirq + s->steal;

    fclose(fp);
}