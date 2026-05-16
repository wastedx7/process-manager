#include "main.h"

// checks if dir in /proc is a pid, return 0 for false, 1 for true
int is_numeric(const char *s){
    while(*s){
        if(!isdigit((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}

// strcpy personal implementation
char* my_strcpy(char* dest, const char* src){
    char* ret = dest;
    while(*src){
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return ret;
}

// strncmp personal implementation
// 0 for both strings equal at n length
// <0 for str1 < str2
// >0 for str1 > str2
int my_strncmp(const char* str1, const char* str2, size_t n){
    size_t i = 0;
    while(i<n && str1[i] && str2[i]){
        if(str1[i] != str2[i]){
            return (unsigned char)str1[i] - (unsigned char)str2[i];
        }
        i++;
    }
    if(i==n) return 0;

    return (unsigned char)str1[i] - (unsigned char)str2[i];
}

// memcpy personal implementation
void* my_memcpy(void* dest, const void* src, size_t bytes){
    char* d = (char*)dest;
    const char* s = (const char*)src;
    for(size_t i=0; i<bytes; i++){
        d[i] = s[i];
    }
    return dest;
}