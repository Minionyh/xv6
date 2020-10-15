#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void 
primes(int *fd)
{
    char buf[4];
    int num = 0;
    int prime = 0;
    int fd1[2];
    pipe(fd1);
    
    while (read(fd[0], buf, 4))
    {
        num++;
        int cur = *((int *)buf);
        if(num == 1){
            prime = *((int *)buf);
            printf("prime %d\n", prime);
        }
        else{
            if(cur % prime == 0){}
            else{
                write(fd1[1], (char *)&cur, 4);
            }
        }
    } 
    close(fd[0]);
    close(fd1[1]);
    if(fork() == 0 && num){
        primes(fd1);
        close(fd[0]);
        exit(0);
    }
    wait(0);
    exit(0);
}

int
main()
{
    int fd[2];
    pipe(fd);
    //char buf[4];
    for(int i = 2; i <=35; i++){
        write(fd[1], (char *)&i, 4);
    }
    close(fd[1]);
    primes(fd);
    exit(0);
}