/*----------------------------------------------------------------------------*/
/* Universidade Federal do Parana                                             */
/*                                                                            */
/* Algoritmos e Estruturas de dados III                                       */
/* Primeiro Trabalho de implementacao                                         */
/*                                                                            */
/* Professora Carmem Satie Hara                                               */
/* Monitores: Guilherme Alex Derenievicz e Jonatas Teixeira                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/


#ifndef _bstree_
#define _bstree_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*----------------------------------------------------------------------------*/
/* Objeto inserido dentro de cada no da arvore                                */ 
/*----------------------------------------------------------------------------*/
typedef int object;

/*----------------------------------------------------------------------------*/
/* Estrutura de arvore binaria sem balanceamento                              */ 
/*----------------------------------------------------------------------------*/
typedef struct node {
    object value;
    char balance;
    struct node *left;
    struct node *right;
} node;

typedef node *tree;


/*----------------------------------------------------------------------------*/
/* Funcoes para trabalhar com o objeto                                        */
/*----------------------------------------------------------------------------*/
void fprintf_object                 (FILE *stream, object o);
object atoo                         (char *s);
int objectcmp                       (object *o1, object *o2);

/*----------------------------------------------------------------------------*/
/* Funcoes para trabalhar com os nos                                          */
/*----------------------------------------------------------------------------*/
node *create_node                   (node **n);
node* destroy_node                  (node **n);

/*----------------------------------------------------------------------------*/
/* Funcoes de rotacoes                                                        */
/*----------------------------------------------------------------------------*/
void rotation_left                  (node **n);
void rotation_right                 (node **n);
void rotation_left_right            (node **n);
void rotation_right_left            (node **n);

/*----------------------------------------------------------------------------*/
/* Funcoes de incersao remocao e busca                                        */
/*----------------------------------------------------------------------------*/
int insert_node                     (node **n, object *o);
int remove_node                     (node **n, object *o);
node *search_node                   (node **n, object *o);


/*----------------------------------------------------------------------------*/
/* Funcoes que podem auxiliar o desenvolvimento do trabalho                   */
/*----------------------------------------------------------------------------*/
object* lower_of_bigger             (node **n);
object* bigger_of_lower             (node **n);
void insert_balance                 (node **n);
void remove_balance                 (node **n);
void show_tree                      (FILE *stream, node *n, int b);

#endif
