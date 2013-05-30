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
/* Funcoes a parte                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Rotaciona o node para a esquerda                                           */
/*----------------------------------------------------------------------------*/
void RotEsqComBal(node **n) {
	node *a = *n;
	node *b = (*n)->right;
	char balln, ballf;
	int baln, balf;

	a->right = b->left;
	b->left = a;

	(*n) = b;


	balln =a->balance;
	ballf =b->balance;
	baln =(balln);
	balf =(ballf);
	printf("Inciando Balaceamento........esq.............\n");
	printf("n->bal=%d f->bal=%d\n", baln, balf);
	// Se o pai tem balanceamento 0
	if(baln ==0){
		printf("balanceamento do pai 0\n");
		if(balf>=0) {
			printf("balanceamento do filho >=0\n");
			baln++;
			balf =1 +balf +baln;
		}
		else {
			printf("balanceamento do filho <0\n");
			baln =1 -balf;
			balf =baln;
		}
	} else { 
		// Senao Se o pai tem balanceamento <0
		if(baln>0) {
			printf("balanceamento do pai >0\n");
			if(balf>=0) {
				printf("balanceamento do filho >=0\n");
				baln =baln +2;
			}
			else {
				printf("balanceamento do filho <0\n");
				baln =2 -balf;
			}
			balf =1 +balf +baln;
		}
		// Senao Se o pai tem balanceamento <0 
		else {
			printf("balanceamento do pai <0\n");
			if(balf>=0) {
				printf("balanceamento do filho >=0\n");
				baln++;
			}
			else {
				printf("balanceamento do filho <0\n");
				baln =2 +baln;
			}
			if(balf<=0) {
				printf("balanceamento do filho <=0\n");
				balf =1 +balf +baln;
			}
			else {
				printf("balanceamento do filho >0\n"); 
				balf++;
			}
		}
	}
	balln =(baln);
	ballf =(balf);
	a->balance =balln;
	b->balance =ballf;
}

/*----------------------------------------------------------------------------*/
/* Rotaciona o node para a direita                                            */
/*----------------------------------------------------------------------------*/
void RotDirComBal(node **n) {
	node *a = *n;
	node *b = (*n)->left;
	char balln, ballf;
	int baln, balf;

	a->left = b->right;
	b->right = a;

	(*n) = b;

	balln =a->balance;
	ballf =b->balance;
	baln =(balln);
	balf =(ballf);
	printf("Inciando Balaceamento.......dir..............\n");
	printf("n->bal=%d f->bal=%d\n", baln, balf);
	// Se o pai tem balanceamento 0
	if(baln ==0){
		printf("balanceamento do pai 0\n");
		if(balf>=0) {
			printf("balanceamento do filho >=0\n");
			baln--;
			balf =-1 +balf +baln;
		}
		else {
			printf("balanceamento do filho <0\n");
			baln =1 -balf;
			balf =1 +baln;
		}
	} else { 
		// Senao Se o pai tem balanceamento <0
		if(baln>0) {
			printf("balanceamento do pai >0\n");
			if(balf>=0) {
				printf("balanceamento do filho >=0\n");
				baln =baln -2;
			}
			else {
				printf("balanceamento do filho <0\n");
				baln =2 -balf;
			}
			balf =-1 +balf +baln;
		}
		// Senao Se o pai tem balanceamento <0 
		else {
			printf("balanceamento do pai >0\n");
			if(balf>=0) {
				printf("balanceamento do filho >=0\n");
				baln--;
			}
			else {
				printf("balanceamento do filho <0\n");
				baln =2 +baln;
			}
			if(balf<=0) {
				printf("balanceamento do filho <=0\n");
				balf =-1 +balf +baln;
			}
			else {
				printf("balanceamento do filho >0\n"); 
				balf++;
			}
		}
	}
	balln =(baln);
	ballf =(balf);
	a->balance =balln;
	b->balance =ballf;
}

/*----------------------------------------------------------------------------*/
/* Insere um node na arvore                                                   */
/*----------------------------------------------------------------------------*/
int insere_node(node **n, object *o) {
	// curret =enderco de uma estrutura de um ponteiro node
	node *current = *n;
	// Se nao tem curret alocado, cria um node  (BASE)
	if( !current ) {
		printf("Node passado para insercao nao esta alocado ainda\n");
		// Se nao conseguir criar um novo node
		if( !(current = create_node(&current))) 
            return 0;
		printf("coloca o objeto no node criado\n");
		current->value = *o;
		*n = current;
		return 1;
	// Senao compara o objeto com o objeto do valor que tem na arvore
	} else if( objectcmp(o,&current->value) == -1 ) {
		printf("Comparou objetos\n");
		if( insert_node(&(current->left), o) == 1){
			printf("Entrou para esquerda - Iniciando Balanceamento\n");
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
			printf("Entrou para Direita - Iniciando Balanceamento\n");
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
/* Funcoes a parte fim                                                            */
/*----------------------------------------------------------------------------*/

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
	// curret =enderco de uma estrutura de um ponteiro node
	node *current = *n;
	// Se nao tem curret alocado, cria um node  (BASE)
	if( !current ) {
		printf("Node passado para insercao nao esta alocado ainda\n");
		// Se nao conseguir criar um novo node
		if( !(current = create_node(&current))) 
            return 0;
		printf("coloca o objeto no node criado\n");
		current->value = *o;
		*n = current;
		return 1;
	// Senao compara o objeto com o objeto do valor que tem na arvore
	} else if( objectcmp(o,&current->value) == -1 ) {
		printf("Comparou objetos\n");
		if( insert_node(&(current->left), o) == 1){
			printf("Entrou para esquerda - Iniciando Balanceamento\n");
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
			printf("Entrou para Direita - Iniciando Balanceamento\n");
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

/*----------------------------------------------------------------------------*/
/* Funcoes a parte                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Inicia Arvore */
/*----------------------------------------------------------------------------*/
node *start_tree(void) {
	node *raiz;
	raiz =create_node(&raiz);
	return raiz;
}

/*----------------------------------------------------------------------------*/
/* Calcula altura da arvore                                                   */
/*----------------------------------------------------------------------------*/
int H_Tree(node *n) {
	int hl, hr;
	if (!n) {
		return 0;
	}
	hl =H_Tree(n->left);
	hr =H_Tree(n->right);
	if (hl>hr) {
		return hl+1;
	}
	else {
		return hr+1; 
	}
}

/*----------------------------------------------------------------------------*/
/* Visualizacao da arvore sem arquivo                                         */
/*----------------------------------------------------------------------------*/
int Conta_Nodo(node *n) {
	int conta;
	if (!n)
		return 0;
	conta =1 + Conta_Nodo(n->left);
	conta =1 + Conta_Nodo(n->right);
	return conta;
}

/*----------------------------------------------------------------------------*/
/* Visualizacao da arvore sem arquivo                                         */
/*----------------------------------------------------------------------------*/
void show_tree_sem_arq (node *n, int b) {
	int i;
	object o;
	if (n == NULL) {
		for (i = 0; i < b; i++) 
			printf("      ");
		printf("\n"); //aponta pra NULL
		return;
	}
	show_tree_sem_arq(n->right, b+1);
	for (i = 0; i < b; i++) 
		printf("      ");
	o =n->value;
    	printf("%d", o);
	printf("(%i)",n->balance);
	printf("\n");

	show_tree_sem_arq(n->left, b+1);
}

void show_tree_sem_arq1 (node *n,int b) {
	printf("-------------------------------------------------------------------------------------------------\n");
	show_tree_sem_arq (n, b);
	printf("-------------------------------------------------------------------------------------------------\n");
}


/*----------------------------------------------------------------------------*/
/* Programa Principal                                                         */
/*----------------------------------------------------------------------------*/
void main () {
	char choose;
	int inicia =1, control =1, h, conta, i=0;
	object valor;
	node *raiz =NULL;
	tree root =raiz;
	scanf("%c", &choose);
	// Enquanto tiver alguma opcao para executar
	while (control) {
		printf("\nIniciando nova secao\n");
		switch (choose) {
		case 'i': printf("++ insercao\n");
				scanf("%d", &valor);
				printf("%d\n", valor);
				insert_node(&root, &valor);
			break;
		case 'b': printf("++ busca\n");
				scanf("%d", &valor);
				printf("%d\n", valor);
				search_node(&root, &valor);
			break;
		case 'r': printf("++ remocao\n");
				scanf("%d", &valor);
				printf("%d\n", valor);
			 	remove_node(&root, &valor);
			break;
		default:	printf("++ nada\n");
				printf("Finalizando o Programa\n");
		 		control =0;
			break;
		}
			// Enquanto for diferente de \n
			while (choose != 10) {      
				scanf("%c", &choose);
			}
		scanf("%c", &choose);
		h =H_Tree(root);
		conta =Conta_Nodo(root);
		printf("altura =%d\n", h);
		printf("nodos =%d\n", conta);
		printf("\nAgora a arvore esta assim:\n");
 		show_tree_sem_arq1 (root, h);
	sleep(1);
	system("clear");
		i++;
		printf("i =%d\n", i);
		if (i ==4) {
			RotEsqComBal(&root);
			printf("\nAgora a arvore esta assim:\n");
 			show_tree_sem_arq1 (root, h);
			RotDirComBal(&root);
			printf("\nAgora a arvore esta assim:\n");
 			show_tree_sem_arq1 (root, h);
			RotDirComBal(&root);
			printf("\nAgora a arvore esta assim:\n");
 			show_tree_sem_arq1 (root, h);
			RotEsqComBal(&root);
			printf("\nAgora a arvore esta assim:\n");
 			show_tree_sem_arq1 (root, h);
			RotEsqComBal(&root);
			printf("\nAgora a arvore esta assim:\n");
 			show_tree_sem_arq1 (root, h);
		}
		printf("\nAgora a arvore esta assim:\n");
 		show_tree_sem_arq1 (root, h);
	}
}


/*---------------------------------------------------------------------------------*/
// Detalhes tecnicos
/*---------------------------------------------------------------------------------*/
// 0x20  //... //   0x32    //...
/*---------------------------------------------------------------------------------*/
//  n    //    //           //
// 0x32  //... // estrutura //...
//       //    //           //
/*---------------------------------------------------------------------------------*/
//  |                  |
//  |                 |||
//  |                |   |
//  |                  |
//  --------------------
//
/*---------------------------------------------------------------------------------*/
// node *n=maloc(sizeof(node))
// &n =0x20 
// n =0x32
/*---------------------------------------------------------------------------------*/
// O ponteiro para estrutura nao sabe o endereco correto aonde a estrutura vai ser 
// alocada, por isso deve se passar o endereco do ponteiro (0x20) neste caso 
// para que quando for alocado espaco para a estrutura, o conteudo do ponteiro 
// passa a ter o valor do endereco aonde foi alocado para a nova estrutura
/*---------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------*/
// Detalhes para primeira implementacao
/*---------------------------------------------------------------------------------*/
//                     -------------------------
//                    || Rotacao a direta de p ||
//                     -------------------------
//               n e k sao conhecidos
//         n                         f
//      {  j   }                   { nk }  
//      (a)  (b)                   ()  (f) 
//   fe //    \\  f              n //    \\ 
// {     }    {  k  }         { nj  }    
//  ()  ()  (e)   (f)        (q) (e)       
// //   \\   //     \\    fe //   \\    
// =     =   =       =   {    }    =    
//                                  
//                    
/*---------------------------------------------------------------------------------*/
