#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int signalReceived = 0;
int pidGlobal;

void signalHandler(int signal){

	if (signal == SIGUSR1){
		signalReceived = 1;
	}
  	if(signal == SIGUSR2)
  	{
    	signalReceived = 2;
  	}
  	if(signal == SIGINT){
  		if (signalReceived == 4){
  			if(pidGlobal>0){
  				sleep(1);
  			}
  			exit(0);
  		}
  		else{
  			if (pidGlobal>0){
  				signalReceived = 4;
  			}
  			else{
  				signalReceived = 3;
  			}
  		}
  	}
}

int main (int argc, char **argv) {

  	int hvalue = 0;
  	int mflag = 0;
  	int index;
  	int c;
  	int pid=1, j=0, status;
  	int signalCounter =0;
  	int numeroHijo;
  	int hijo;
  	int senal=0;
  	int *listadoHijos;
  	int ctrlC=0;
  	opterr = 0;

  while ((c = getopt (argc, argv, "h:m")) != -1)
    switch (c)
      {
      case 'h':	
        sscanf(optarg, "%d", &hvalue);
        break;
      case 'm':
        mflag = 1;
        break;
      case '?':
        if (optopt == 'h'){
          fprintf (stderr, "Opcion -%c requiere un argumento.\n", optopt);
        }
        else if (isprint (optopt))
          fprintf (stderr, "Opcion desconocida `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Opcion con caracter desconocido `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }

  if (hvalue == 0){
    fprintf (stderr, "Debe ingresar un argumento valido para h\n");
    return 1;
  }

  //pidP = getpid();

  //pid = fork();
  signal(SIGUSR1, signalHandler);
  signal(SIGUSR2, signalHandler);
  signal(SIGINT, signalHandler);
  listadoHijos = (int*)malloc(sizeof(int)*hvalue);
  while(j<hvalue)
  {
    if(pid>0)
    {
      pid = fork();
      if(pid == 0){
	      numeroHijo = j+1;
      }
      else if (pid>0){
      	listadoHijos[j] = pid;
      }

      
    }
    else if(pid<0){
      printf("ERROR, FINALIZANDO EJECUCION... \n");
      exit(1);
    }
    j++;
  }
  
  if (mflag==1){
	  if (pid == 0){
		printf("Soy el proceso %i y mi pid es: %i \n", numeroHijo, getpid());
	  }
  }
  pidGlobal = pid;
  while(1){
    if (pid>0){
      sleep(1);
      printf("Ingresar numero de hijo y señal a enviar (X - Y): \n");
      scanf("%d - %d", &hijo, &senal);

      if (hijo>hvalue || hijo<=0){
      	printf("\nNo existe el hijo descrito\n");
      	senal=0;
      }
      else{
      	if (senal == 16)
        {
      		kill(listadoHijos[hijo-1], SIGUSR1);
      		senal = 0;
      	}
        else if (senal == 17)
        {
          kill(listadoHijos[hijo-1], SIGUSR2);
          senal = 0;
        }
        else if (senal == 15){
        	kill(listadoHijos[hijo-1], SIGTERM);
    		senal = 0;
        }
      }
    }
    if (signalReceived == 1){
    	signalCounter++;
    	if (signalCounter == 1){
    		printf("Mi pid es: %i y he recibido esta senal %i vez\n", getpid(), signalCounter);
    	}
    	else{
    		printf("Mi pid es: %i y he recibido esta senal %i veces\n", getpid(), signalCounter);
    	}
    	signalReceived = 0;
    }
    else if(signalReceived == 2)
    {
      fork();
      signalReceived = 0;
    }
    else if (signalReceived == 3){
    	if (pid == 0){
    		printf("Soy el hijo con pid: %i y estoy vivo aun\n", getpid());
    	}
    	signalReceived = 4;
    }
  }
}

