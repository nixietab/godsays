#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "happy_txt.h"

#define TAKE 32
#define MAX_WORDS 10000

int main(int argc, char **argv) {
    char *words[MAX_WORDS];
    size_t n = 0;
    int lines = (argc > 1 && strcmp(argv[1], "-l") == 0);

    unsigned int seed = 0;
    FILE *f = fopen("/dev/urandom","rb"); if(f){fread(&seed,sizeof seed,1,f); fclose(f);}
    if(!seed) seed = (unsigned)time(NULL) ^ (unsigned)getpid();
    srand(seed);

    char *buf = (char *)Happy_TXT; buf[Happy_TXT_len] = '\0';
    for(char *tok=strtok(buf,"\n\r"); tok && n<MAX_WORDS; tok=strtok(NULL,"\n\r"))
        if(*tok) words[n++] = tok;

    if(!n) return 1;

    for(size_t i=n-1;i>0;i--){size_t j=rand()%(i+1); char*t=words[i]; words[i]=words[j]; words[j]=t;}

    size_t take = n < TAKE ? n : TAKE;
    for(size_t i=0;i<take;i++){
        if(lines) fputs(words[i],stdout), putchar('\n');
        else { if(i) putchar(' '); fputs(words[i],stdout);}
    }
    if(!lines) putchar('\n');
    return 0;
}
