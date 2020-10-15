#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]){
    if(argc < 2){
        printf("Xargs need more args\n");
        exit(0);
    }
    int i;

    char buf;
    char tmp[32];
    char *arg[32];
    char *execarg[32];
    int c = 0;
    int argC = 0;

    for(i = 0; i < 32; i++){
        arg[i] = (char *)malloc(32 * sizeof(char));
        execarg[i] = (char *)malloc(32 * sizeof(char));
    }
    //printf("%d\n", argc);
    for(i = 1; i < argc; i++){
        strcpy(execarg[i-1], argv[i]);
        //printf("%s\n", argv[i]);
    }

    while(read(0, &buf, 1)){


        if(buf != ' ' && buf != '\n'){
            tmp[c] = buf;
            c++;
        }
        else{
            tmp[c] = 0;
            if(c){
                strcpy(arg[argC], tmp);
            }
            c = 0;
            argC++;
        }

        if(buf == '\n'){
            int j = argc-1;
            int k = 0;
            for(k = 0; k < argC; k++){
                //printf("%s\n",arg[k]);
                strcpy(execarg[j+k], arg[k]);
            }
            execarg[j+k] = 0;
            //printf("%s\n",execarg[j+k]);
            
            if(fork() == 0){
                exec(execarg[0], execarg);
                exit(0);
            }
            wait(0);
            
            argC = 0;
            c = 0;
            
        }
    }


    

    exit(0);
}