#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char **argv) {
  int hvalue = 0;
  int mflag = 0;
  int index;
  int c;
  int pid=1, j=0, status;
  int cont =0;
  int numeroHijo, opcion2=0;
  char opcion[5];
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
  printf("h: %i\n", hvalue );


  //pidP = getpid();

  //pid = fork();
  while(j<hvalue)
  {
    if(pid>0)
    {
      pid = fork();
      if(pid == 0){
	numeroHijo = j+1;
	printf("%d\n", numeroHijo);
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

  if(pid>0)
  {
    while(cont < 3)
    {
      printf("Ingresar numero de hijo y señal a enviar (X - Y): \n");
      scanf("%c", &opcion);
      printf("dfgfd%s\n", opcion);
      
      cont++;
    }
    
  }
}

