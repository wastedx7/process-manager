#include "main.h"

int main(){
    
    Process p;

    read_processes_stats(&p);

    printf("utime : %ld\n", p.utime);
    printf("stime : %ld\n", p.stime);

    return 0;
}