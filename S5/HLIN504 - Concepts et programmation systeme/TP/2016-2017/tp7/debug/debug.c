#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ucontext.h>
#include "debug.h"

static struct sigaction action;

void debug(int * signals) {
    action.sa_handler = debug_handler;
    int * ptr = signals;
    
    while(*ptr != -1) {
        sigaction(*ptr , &action , NULL);
        ptr++;
    }
}

void debug_handler(int signal) {
    printstack(1);
    exit(EXIT_FAILURE);
}