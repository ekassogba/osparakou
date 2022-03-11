#include <stdlib.h>
struct node{
  int val;
  struct node *next;
};

/**
   Initialise une liste vide
**/
struct node *init_node(void);

/** Ajoute la valeur à la tête de la liste et retourne
 *  la nouvelle tête (head)
 **/
struct node *addHead(struct node *head, int val);

/** Ajoute l'élément à la fin de la liste.
 * La tête de liste ne change pas
 **/
void addTail(struct node *head, int val);

/**
 * alloue de la mémoire pour un nouveau noeud et retourne ce noeud
 **/
struct node *new_node(int val);

/** affiche tous les éléments de la liste
 *  au format val: <valeur>
 **/
void display_list(struct node *head);

int main(int argc, char *argv[]){
   struct node *head;
   head = init_node();
   int i;
   for(i = 0; i < 100; i++  )
      head = addHead(head, i*2);
   display_list(head);
   return 0;
}

struct node *init_node(void){
  struct node * n = (struct node*)malloc(sizeof(struct node));
  n->val = -1;
  n->next = NULL;
  return n;
}

/**
 * alloue de la mémoire pour un nouveau noeud et retourne ce noeud
 * @pre val
 * @ret alloue une mémoire de taille sizeof(struct node) sur le heap
 *   et retourne un pointeur vers cette mémoire et initialise le nouveau
 *   noeud à val
 **/
struct node *new_node(int val){
    struct node *n = (struct node*)malloc(sizeof(struct node));
    n->val = val;
    return n;
}

/** Ajoute la valeur à la tête de la liste et retourne
 *  la nouvelle tête (head)
 *  @pre head != NULL
 *  @ret crée un nouveau neoud et l'ajoute à la tête de la liste
 *       le nouveau noeud devient la tête de la liste
 **/
struct node *addHead(struct node *head, int val){
    if(head->val == -1){ // la liste est vide
       head->val = val;
       return head;
    }
    struct node *n = new_node(val);
    n->next = head;
    head = n;
    return head;
}

/** affiche tous les éléments de la liste
 *  au format val: <valeur>
 *  @pre head != NULL
 **/
void display_list(struct node *head){
    if(head==NULL)
       return;
    struct node *next;
    next = head->next;
    printf("val: %d ", head->val);
    while(next){
       printf("val: %d ", next->val);
       next = next->next;
    }
    return;
}
