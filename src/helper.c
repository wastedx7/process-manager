#include "main.h"

// checks if dir in /proc is a pid, return 0 for false, 1 for true
int is_numeric(const char *s){
    while(*s){
        if(!isdigit((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}
