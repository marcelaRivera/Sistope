#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



void do_nothing(){
	sleep(1); // 10 second
}

int main(){
	int pid, j, status;
	int pidP; 
	int NFORKS  = 5;
	for (j=0; j < NFORKS; j++){
		pid = fork();
		pidP = getppid();
		if(pidP>0 && pid>0)
		{
			if ((pid = fork()) < 0)
			{
			printf("no se pudo crear hijo\n");
			exit(1);
			}

			if (pid == 0)
			{ // hijo
		    	do_nothing();
				exit(0);
			}
		/*else{ // padre
			waitpid(pid, &status, 0);
			printf("%d\n", pid);
			exit(0);
		}*/
		}
		
	}
}