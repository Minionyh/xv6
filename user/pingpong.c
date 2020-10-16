#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
mian()
{
    int p[2];
    pipe(p);
    char buf[5];

    int pid = fork();
    if(pid == 0){
        int n;
        n = read(p[0], buf, 1);
        if(n < 1){
            write(2, "error",6);
            exit(1);
        }
        else{
            close(p[0]);
            printf("%d: received ping\n", getpid());
            write(p[1], " ", 1);
            close(p[1]);
            exit(0);
        }
    }
    else{
        write(p[1], " ", 1);
        wait(0);
        int n;
        n = read(p[0], buf, 1);
        if(n < 1){
            write(2, "error",6);
            exit(1);
        }
        printf("%d: received pong\n", getpid());
        exit(0);
    }
}