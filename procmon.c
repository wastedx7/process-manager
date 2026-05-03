
// basic structure 
typedef struct {
    int pid;
    char name[1024];
    unsigned long utime, stime;
    unsigned long total_time;
    long memory; // VmRss (amount of process mem in ram)
    float cpu;
} Process; 