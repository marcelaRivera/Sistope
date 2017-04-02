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
  int pidP;
  int *arreglo;

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
  printf("caca %i\n", pid);
 arreglo = (int*)malloc(sizeof(int)*hvalue);
  while(j<hvalue)
  {
    if(pid>0)
    {
      pid = fork();
      printf("pid %i \n", pid);
      pidP = getpid();
      arreglo[j] = pidP;
      printf("k%i \n", arreglo[j]);
      j++;
      
    }
    else if (pid == 0)
    {
      j++;
      exit(0);
      break;
    }
    else
    {
      printf("error\n");
      j++;
    }
   // j++;
  }

  if(pid>0)
  {
  for(j=0; j<hvalue; j++)
  {
    printf("soy el proceso %i y mi pid es: %i \n", j, arreglo[j]);
  }
  return 0;
}
}
