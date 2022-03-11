#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define MEMSIZE 1000 /* taille de la mémoire partagée*/

key_t shm_key; /*clé de la mémoire partagée*/
int shmid; /* id de la mémoire partagée*/

void mem_attach(int shmid,void **adresse);
int init();
void mem_detach(void **adresse);

int main(int argc, char *argv[]){
  int i;
  pid_t pid[4];
  /** Initialisation de la mémoire partagée pour les fils
   **/
  short *shmval;
  int ret;
  ret = init();
  if(ret < 0)
    exit(1);
  mem_attach(shmid, (void**)&shmval);
  *shmval = 0;
  for(i = 0; i < 4; i++){
    pid[i] = fork();
    if(pid[i]<0){
      /*On gère l'erreur*/
      fprintf(stderr, "Erreur lors de la création du fils(%d)\n", errno);
      return 1;
    }
    if(pid[i] == 0){
      /* Dans le fils*/
      int ret;
      ret = execve("./shm", argv,NULL);
    }
    else{
   
    }
  }
  
  for(i = 0; i < 4; i++){
      int status;
      wait(&status);
  }
  printf("Valeur finale de la mémoire partagée (%d)\n", *shmval);
  shmctl(shmid, IPC_RMID, NULL);
}


int init(){
  shm_key = ftok("shared_mem.key", 256); // création de la clé
  if(shm_key < 0){ // la clé n'a pas pu être créée
    printf("Impossible de créer la clé (%s)\n", strerror(errno));
    return shm_key;
  }
  /* Création de la mémoire partagée */
  fprintf(stderr, "key %d\n", shm_key);
  shmid = shmget(shm_key, MEMSIZE, IPC_EXCL | IPC_CREAT | 0666); 
  if (shmid<0){ 
    if(errno!=EEXIST)
      return shmid;
    /* Si la mémoire partagée existe déjà , il faut obtenir son id*/
    shmid = shmget(shm_key, MEMSIZE, 0666);
    if(shmid < 0)
      return shmid;
  }
  return 1;
}


void mem_attach(int shmid,void **adresse){
  /* Le processus attache une adresse dans son 
   *  espace mémoire à la mémoire partagée
   */
  *adresse=(short *)shmat(shmid, NULL,0);
  if (*adresse==(void *)-1) exit(1);
}

void mem_detach(void **adresse){
  /* Le processus détache l'adresse de son 
   *  espace mémoire de la mémoire partagée
   */
  shmdt(*adresse);
}
