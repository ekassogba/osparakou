#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define NPROCS 4 // c'est une déclaration du pré-processeur

/** Je crée NPROCS processus pour
 *  vous apprendre à créer plusieurs
 *  processus. Soyez donc très attentifs
 *  à ce que je fais et comment je le fais.
 **/

int main(int argc, char *argv[]){
  int i;
  pid_t pid[NPROCS];
  for(i = 0; i < NPROCS; i++){
    pid[i] = fork();
    if(pid[i]<0){
      /*On gère l'erreur*/
      fprintf(stderr, "Erreur lors de la création du fils(%d)\n", errno);
      return 1;
    }
    if(pid[i] == 0){
      /* Dans le fils*/
      fprintf(stdout, "Je suis (%d), mon père (%d)\n", getpid(), getppid());
      // Enlève l'instrution break pour voir l'effet.
      break;
    }
    else{

    }
  }
  // Enlève cette boucle pour voir l'effet
  /** Avez vous compris à quoi je sui utile?
   *  Sinon, réfléchissez un peu**/
  for(i = 0; i < NPROCS; i++){
      int status;
      wait(&status);
  }
  return 0;
}
