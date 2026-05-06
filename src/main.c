#include "main.h"

int main(){
    
    CPUStats s;

    read_cpu_stats(&s);  // called once

    printf("CPU Stats:\n");
    printf("User: %llu\n", s.user);
    printf("Nice: %llu\n", s.nice);
    printf("System: %llu\n", s.system);
    printf("Idle: %llu\n", s.idle);
    printf("IOWait: %llu\n", s.iowait);
    printf("IRQ: %llu\n", s.irq);
    printf("SoftIRQ: %llu\n", s.softirq);
    printf("Steal: %llu\n", s.steal);
    printf("Total: %llu\n", s.total);

    return 0;
}