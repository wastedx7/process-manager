#include "main.h"

int main(){
    Process process[MAX_PROCS];
    size_t n = count_procs(process, MAX_PROCS);
    for(size_t i=0; i<n; i++){
        printf("PID: %d | Name: %s | utime: %lu | stime: %lu | VmRSS: %ld KB\n",
               process[i].pid,
               process[i].name,
               process[i].utime,
               process[i].stime,
               process[i].memory);
    }    
    return 0;
}