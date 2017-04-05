#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>


int signalReceived = 0;//variable que permite identificar el tipo de acción, según la señal ingresada por el usuario
int pidGlobal;

/*Entrada: Recibe valor de la señal
Salida: comportamiento de señales
Funcion: asignar el comportamiento de las distintas señales */
void signalHandler(int signal){
//Se compara el tipo de señal correspondiente
	if (signal == SIGUSR1){
		signalReceived = 1; //se asigna un valor para la variable global
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


/* Función que sirve para crear los procesos hijos y permitir la comunicación de señales
Entrada: cantidad de hijos por crear
Salida: procesos creados y opción para interactuar enviando señales a los procesos*/

int main (int argc, char **argv) {

  	int hvalue = 0; //parametro de entrada
  	int mflag = 0; //bandera
  	//int index;
  	int c;
  	int pid=1/*variable para guardar el pid de los procesos*/, j=0 /*contador*/;
  	int signalCounter =0; //contador para almacenar cantidad de veces que ha sido llamada la señal sigurs1
  	int numeroHijo;//variable que representa un contador, el cual permite identificar a un proceso hijo en particular
  	int hijo;//variable que almacena al hijo que se le quiere enviar una señal
  	int senal=0; //tipo de señal a enviar
  	int *listadoHijos; //arreglo para guardar los pid de cada hijo
  	int ctrlC=0;
  	opterr = 0;

//el siguiente ciclo se utiliza para recibir los parametros de entrada usando getopt
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

  
  //se activan las señales
  signal(SIGUSR1, signalHandler);
  signal(SIGUSR2, signalHandler);
  signal(SIGINT, signalHandler);
  listadoHijos = (int*)malloc(sizeof(int)*hvalue);

  /*El siguiente ciclo permite crear n procesos hijos, dado el parametro de entrada hvalue*/
  while(j<hvalue)
  {
    if(pid>0) //proceso padre
    {
      pid = fork(); //se crea un nuevo proceso
      if(pid == 0)//proceso hijo
      {
	      numeroHijo = j+1; //contador de procesos creados
      }
      else if (pid>0){ //proceso padre
      	listadoHijos[j] = pid; //almacena pid de hijos
      }

      
    }
    //en caso de no poder crearse hijo:
    else if(pid<0)
    {
      printf("ERROR, FINALIZANDO EJECUCION... \n");
      exit(1);
    }
    j++;
  }
  
  //en el caso de activarse bandera
  if (mflag==1)
  {
	  if (pid == 0)//proceso hijo
    {
		printf("Soy el proceso %i y mi pid es: %i \n", numeroHijo, getpid());
	  }
  }
  pidGlobal = pid;
  while(1)
  {
    if (pid>0) //proceso padre
    {
      sleep(1); //esperar un segundo
      printf("Ingresar numero de hijo y señal a enviar (X - Y): \n"); 
      scanf("%d - %d", &hijo, &senal);  //se guardan nuevos parametros de entrada, como hijo y señal.

      if (hijo>hvalue || hijo<=0) //en caso de escoger un proceso invalido:
      { 
      	printf("\nNo existe el hijo descrito\n");
      	senal=0;
      }
      else  //sí el proceso existe:
      {
      	if (senal == 16)
        {
      		kill(listadoHijos[hijo-1], SIGUSR1); //se realiza la comunicación
      		senal = 0; //se reinicia valor de señal
      	}
        else if (senal == 17)
        {
          kill(listadoHijos[hijo-1], SIGUSR2);
          senal = 0;
        }
        else if (senal == 15)
        {
        	kill(listadoHijos[hijo-1], SIGTERM);
    		senal = 0;
        }
      }
    }

//A continuación se identifica la acción correspontiente que se debe realizar, según el tipo de señal recibida.

    if (signalReceived == 1) //en caso de ser la señal SIGURS1
    {
    	signalCounter++; //aumenta en uno el contador.
    	if (signalCounter == 1) //en caso de ser el primer llamado
      {
    		printf("Mi pid es: %i y he recibido esta senal %i vez\n", getpid(), signalCounter);
    	}
    	else //mas de uno
      {
    		printf("Mi pid es: %i y he recibido esta senal %i veces\n", getpid(), signalCounter);
    	}
    	signalReceived = 0;
    }
    else if(signalReceived == 2) //En caso de recibir SIGURS2
    {
      fork();
      signalReceived = 0;
    }
    else if (signalReceived == 3) //En caso de recibir SIGTERM
    {
    	if (pid == 0) //proceso hijo
      {
    		printf("Soy el hijo con pid: %i y estoy vivo aun\n", getpid());
    	}
    	signalReceived = 4;
    }
  }
}

