#include "bs-tree.h"

/*----------------------------------------------------------------------------*/
/* Imprime um object em stream                                                */
/*----------------------------------------------------------------------------*/
void fprintf_object(FILE *stream, object o) {
    fprintf(stream, "%d", o);
}

/*----------------------------------------------------------------------------*/
/* Transforma um ASCII em um object                                           */
/*----------------------------------------------------------------------------*/
object atoo(char *s) {
    return atoi(s);
} 

/*----------------------------------------------------------------------------*/
/* Faz a compraracao entre dois objects                                       */
/*----------------------------------------------------------------------------*/
int objectcmp(object *o1, object *o2) {
  return *o1 < *o2 ? -1 : *o1 > *o2 ? 1 : 0;
}

/*----------------------------------------------------------------------------*/
/* Cria e aloca um novo no                                                    */
/*----------------------------------------------------------------------------*/
node *create_node(node **n) {
	node *new_node;
	if ( !(new_node = malloc(sizeof(node)))) {
		 fprintf (stderr, "Error while running Binary Tree Library: Alloc node failed.\n");
		 exit (1);
	}
	new_node->value = 0;
	new_node->balance = 0;
	new_node->left = NULL;
	new_node->right = NULL;
	*n = new_node;
	return *n;
}

/*----------------------------------------------------------------------------*/
/* Visualizacao da arvore                                                     */ 
/*----------------------------------------------------------------------------*/
void show_tree (FILE *stream, node *n, int b) {
	int i;
	if (n == NULL) {
		for (i = 0; i < b; i++) 
			fprintf(stream, "      ");
		fprintf(stream, "*\n");
		return;
	}
	show_tree(stream, n->right, b+1);
	for (i = 0; i < b; i++) 
		printf("      ");
        fprintf_object (stream, n->value);
	fprintf(stream, "(%i)",n->balance);
	fprintf(stream, "\n");

	show_tree(stream, n->left, b+1);
}

/*----------------------------------------------------------------------------*/
/* Destroi e libera a memoria alocada para o respectivo node                  */
/*----------------------------------------------------------------------------*/
node* destroy_node(node **n) {
	if (*n) {
		(*n)->value = 0;
		(*n)->balance = 0;
		(*n)->left = NULL;
		(*n)->right = NULL;
		free(*n);
	}
	return NULL;
}

/*----------------------------------------------------------------------------*/
/* Devolve o menor dos maiores objetos inserido na arvore apartir do node n   */
/*----------------------------------------------------------------------------*/
object* lower_of_bigger(node **n) {
	if ((*n)->left == NULL)
		return (&((*n)->value));
 	else 
		return lower_of_bigger(&(*n)->left);
}

/*----------------------------------------------------------------------------*/
/* Devolve o maior dos menores objetos inserido na arvore apartir do node n   */
/*----------------------------------------------------------------------------*/
object* bigger_of_lower(node **n) {
	if ((*n)->right == NULL)
		return (&((*n)->value));
 	else 
		return bigger_of_lower(&(*n)->right);
}

/*----------------------------------------------------------------------------*/
/* Balanceamento - Ajusta apos a insercao                                     */
/*----------------------------------------------------------------------------*/
void insert_balance(node **n) {
        if ((*n)->balance == -1){
                (*n)->left->balance=1;
                (*n)->right->balance=0;
        } else if ((*n)->balance == 1 ) {
                (*n)->left->balance=0;
                (*n)->right->balance=-1;
        } else if ((*n)->balance == 0 ) {
                (*n)->left->balance=0;
                (*n)->right->balance=0;
        }
        (*n)->balance=0;
}

/*----------------------------------------------------------------------------*/
/* Balanceamento - Ajusta apos a remocao                                      */                           
/*----------------------------------------------------------------------------*/
void remove_balance(node **n) {
	if (*n) {
		if ((*n)->left && (*n)->right) {
			if ( abs( ((*n)->left)->balance ) == abs( ((*n)->right)->balance ) )
			(*n)->balance = 0;
			else
				if ( ((*n)->left)->balance == 0 )
					(*n)->balance = -1;
				else
					(*n)->balance = 1;
		}
		else
			if ( (! (*n)->left) && (! (*n)->right) )
				(*n)->balance = 0;
			else
				if ((*n)->left)
					(*n)->balance = 1;
				else
					(*n)->balance = -1;
	}
}

/*----------------------------------------------------------------------------*/
/* Rotaciona o node para a esquerda                                           */
/*----------------------------------------------------------------------------*/
void rotation_left(node **n) {
	node *a = *n;
	node *b = (*n)->right;

	a->right = b->left;
	b->left = a;

	(*n) = b;
}

/*----------------------------------------------------------------------------*/
/* Rotaciona o node para a direita                                            */
/*----------------------------------------------------------------------------*/
void rotation_right(node **n) {
	node *a = *n;
	node *b = (*n)->left;

	a->left = b->right;
	b->right = a;

	(*n) = b;
}

/*----------------------------------------------------------------------------*/
/* Rotaciona o node para esquerda direita                                     */
/*----------------------------------------------------------------------------*/
void rotation_left_right(node **n) {
	node *a = *n;
	node *b = a->left;
	node *c = b->right;

	a->left = c->right;
	b->right = c->left;
	c->right = a;
	c->left = b;

	(*n) = c;
}

/*----------------------------------------------------------------------------*/
/* Rotaciona o node para direita esquerda                                     */
/*----------------------------------------------------------------------------*/
void rotation_right_left(node **n) {
	node *a = *n;
	node *b = a->right;
	node *c = b->left;

	a->right = c->left;
	b->left = c->right;
	c->left = a;
	c->right = b;

	(*n) = c;
}

/*----------------------------------------------------------------------------*/
/* Insere um node na arvore                                                   */
/*----------------------------------------------------------------------------*/
int insert_node(node **n, object *o) {
	node *current = *n;
	if( !current ) {
		if( !(current = create_node(&current))) 
            return 0;
		current->value = *o;
		*n = current;
		return 1;
	} else if( objectcmp(o,&current->value) == -1 ) {
		if( insert_node(&(current->left), o) == 1){
			current->balance++;
			if (current->balance == 2 ) {
				if ( (current->left)->balance == 1) {
					rotation_right(&current);
					current->balance = 0;
					(current->right)->balance = 0;
				}
				else if ( (current->left)->balance == -1) {
					rotation_left_right(&current);
					insert_balance (&current);
				}
				*n = current;
			}
			return (current->balance > 0);
		}
	} else if( objectcmp(o,&current->value) == 1 ) {
		if( insert_node(&(current->right), o) == 1){
			current->balance--;
			if ( current->balance == -2 ) {
				if ( (current->right)->balance == -1) {
					rotation_left(&current);
					current->balance = 0;
					(current->left)->balance = 0;
				}
				else if ( (current->right)->balance == 1) {
					rotation_right_left(&current);
					insert_balance(&current);
				}
				*n = current;
			}
			return (current->balance < 0);
		}
	}
	return 0;
}

/*----------------------------------------------------------------------------*/
/* Remocao                                                                    */
/*----------------------------------------------------------------------------*/
int remove_node(node **n, object *o) {
	if( ! *n )
		return 0;
	if( objectcmp(o,&((*n)->value)) == -1 ) {
		if( remove_node(&((*n)->left), o) == 1){
			(*n)->balance -= 1;
			if ( (*n)->balance == -2 ) {
				if ( (*n)->right ){
					if ( ((*n)->right)->balance == 1)
						rotation_right_left(n);
					else if ( ((*n)->right)->balance == 0)
						rotation_left(n);
					else if ( ((*n)->right)->balance == -1)
						rotation_left(n);
				}
				remove_balance( &((*n)->left)  );
				remove_balance( &((*n)->right) );
				remove_balance(n);
			}
			return ((*n)->balance == 0);
		}
	}
 	else if( objectcmp(o,&((*n)->value)) == 1 ) {
		if( remove_node(&((*n)->right), o) == 1){
			(*n)->balance += 1;
			if ( (*n)->balance == 2 ) {
				if ( (*n)->left ) {
					if ( ((*n)->left)->balance == 1 )
						rotation_right(n);
					else if ( ((*n)->left)->balance == 0)
						rotation_right(n);
					else if ( ((*n)->left)->balance == -1)
						rotation_left_right(n);
				}
				remove_balance( &((*n)->left)  );
				remove_balance( &((*n)->right) );
				remove_balance(n);
			}
			return ((*n)->balance == 0);
		}
	}
	else if ( objectcmp(o, &((*n)->value)) == 0) {
		if ((*n)->left && (*n)->right) {
			object* lower = lower_of_bigger(&((*n)->right));
			(*n)->value =  *lower;
			if (remove_node (&((*n)->right), lower) == 1) { //IDEM RIGHT ¬¬
			(*n)->balance += 1;
			if ( (*n)->balance == 2 ) {
				if ( (*n)->left ) {
					if ( ((*n)->left)->balance == 1 )
						rotation_right(n);
					else if ( ((*n)->left)->balance == 0)
						rotation_right(n);
					else if ( ((*n)->left)->balance == -1)
						rotation_left_right(n);
				}
				remove_balance( &((*n)->left)  );
				remove_balance( &((*n)->right) );
				remove_balance(n);
			}
			return ((*n)->balance == 0);

			}
		}
		else {
			node *m = *n;
			if ((*n)->left)
				*n = (*n)->left;
			else 
				*n = (*n)->right;
			destroy_node(&m);
			remove_balance (n);
		return 1;	
		}
}

	return 0;
}

/*----------------------------------------------------------------------------*/
/* Busca um objeto dentro dos nodes da arvore,                                */ 
/* quando escontra devolve um ponteiro para o node                            */
/*----------------------------------------------------------------------------*/
node *search_node(node **n, object *o) {
	node *cptree = *n;
	while (cptree && ( objectcmp(o, &cptree->value) != 0 ) ) {
		if (objectcmp(o, &cptree->value) == -1 )
			cptree = cptree->left;
		else
			cptree = cptree->right;
	}
	return cptree;
}
