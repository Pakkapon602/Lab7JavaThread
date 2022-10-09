#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
int notDone = 1; int cnt = 0;
void mySIGhandler(int sig) {
        signal(SIGALRM,SIG_IGN);
        //breaks infinite loop by reset notDone
        notDone = 0;
        ///printf("loop should break\n");
}
int main(void) {
        ////install handler
        signal(SIGALRM,mySIGhandler);
        pid_t pid = fork();

        if (pid == 0) {
        ////let parent enters loop (manual synchronization)
                //sleep(4); //let parent enters loop
                printf("child created\n");
                sleep(4);
                kill(getppid(),SIGALRM);
                while(1);
                printf("This line should not be shown\n");


                //printf("sending SIGALRM\n");

                exit(0); // send signal and die
        } else {
                printf("parent wait for SIGALRM\n");
                while (notDone) cnt++; //infinite loop
        }
        ////Could be time instead of cnt
        printf("it takes %d\n",cnt);
        kill(pid,SIGKILL);
        return 0;
}
