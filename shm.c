#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <assert.h>
#include <unistd.h>


/**
 * Ce programme permet de comprendre le fonctionnement d'une mémoire partagée.
 * La mémoire partagée est créée à l'aide d'une clé qui elle même est créée à
 * l'aide d'un fichier et d'un id. Le contenu de la mémoire partagée survie au
 * processus. Vous pouvez le remarquer à chaque appel de du programme, le pro-
 * gramme a la possibilité de lire le contenu de la mémoire partagée et de modi-
 * fier son contenu. Ce contenu peut aussi être modifier par un processus qui a
 * les autorisation pour le faire.
 **/

#define MEMSIZE 1000 /* taille de la mémoire partagée*/

key_t shm_key; /*clé de la mémoire partagée*/
int shmid; /* id de la mémoire partagée*/

int init(){
  shm_key = ftok("shared_mem.key", 256); // création de la clé
  if(shm_key < 0){ // la clé n'a pas pu être créée
    printf("Impossible de créer la clé (%s)\n", strerror(errno));
    return shm_key;
  }
  /* Création de la mémoire partagée */
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

int main(int argc, char *argv[]){
  short *shmval;
  short localval;
  int ret;
  ret = init();
  if(ret < 0)
    return -1;
  mem_attach(shmid, (void**)&shmval);
  
  /* tentative de lecture du contenu de la mémoire partagée*/
  printf("Lecture du contenu de la mémoire partagée\n");
  localval = *shmval;
  printf("valeur lue par proc(%d) :%d\n", getpid(), localval);
  printf("je dors un peu\n");
  sleep(2);
  
  printf("Je modifie le contenu de la mémoire partagé\n");
  *shmval = localval+1;
  mem_detach((void**)&shmval);
  return 0;
}
