#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



void do_nothing(){
	sleep(5); // 10 second
}

int main(){
	int pid, j=0, status;
	int pidP; 
	int NFORKS  = 3;
	//pidP = getpid();

	//pid = fork();
	printf("caca %i\n", pid);
	while(j<2)
	{
		if(pid>0)
		{
			pid = fork();

			printf("caca2f %i \n", pid);
			j++;
		}
	}
	
	
}