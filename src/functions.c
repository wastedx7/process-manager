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
    fscanf(fp, "%s %llu %llu %llu %llu %llu %llu %llu %llu",
           label, &s->user, &s->nice, &s->system, &s->idle, &s->iowait, &s->irq, &s->softirq, &s->steal);

    s->total = s->user + s->nice + s->system + s->idle + s->iowait + s->irq + s->softirq + s->steal;

    fclose(fp);
}

// to read utime and stime !!
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
    my_strcpy(list->name, com);     // copy name into com

    char* ptr = buff;   // pointer to a char to buff
    size_t field = 1;          // field counter in buff

    while(field < 14 && *ptr){
        if(*ptr == ' ') field++;
        ptr++;
    }

    sscanf(ptr, "%lu %lu", &list->utime, &list->stime);  // read from buff and store the utime and stime
    return 0;
}

// read vmrss in KB
int read_vmrss(Process *list){
    char path[256];
    char line[256];

    snprintf(path, sizeof(path), "/proc/%d/status", list->pid);
    FILE *f = fopen(path, "r");
    if(!f) return -1;

    while(fgets(line, sizeof(line), f)){
        if(my_strncmp(line, "VmRSS:", 6) == 0){
            sscanf(line, "VmRSS: %ld", &list->memory);
            fclose(f);
            return 0;
        }
    }
    fclose(f);
    return -1;
}

// return the number of processes
int count_procs(Process* list, int max){
    DIR *dir = opendir("/proc");
    if(!dir){
        perror("opendir");
        return -1;
    }

    // entry is the pointer to the next directory
    struct dirent* entry;
    int count = 0;

    // continue until the next dir is not null, also should be numeric only
    while((entry = readdir(dir)) != NULL && count < max){
        if(!is_numeric(entry->d_name)) continue;

        // atoi is ascii to integer
        int pid = atoi(entry->d_name);
        
        // init all the fields to 0
        Process p = {0};
        p.pid = pid;

        if(read_processes_stats(&p) != 0)
            continue;
        read_vmrss(&p);

        list[count++] = p;
    }
    closedir(dir);
    return count;
}