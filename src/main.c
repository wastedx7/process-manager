#include "main.h"

int main() {
    Process process[MAX_PROCS];
    size_t n = count_procs(process, MAX_PROCS);

    // Header
    printf("+--------+----------------------+--------------+--------------+--------------+\n");
    printf("| %-6s | %-20s | %-12s | %-12s | %-12s |\n",
           "PID", "Name", "utime", "stime", "VmRSS KB");
    printf("+--------+----------------------+--------------+--------------+--------------+\n");
    // Rows
    for (size_t i = 0; i < n; i++) {
        printf("| %-6d | %-20s | %-12lu | %-12lu | %-12ld |\n",
               process[i].pid,
               process[i].name,
               process[i].utime,
               process[i].stime,
               process[i].memory);
    }
    // Footer
    printf("+--------+----------------------+--------------+--------------+--------------+\n");

    return 0;
}
