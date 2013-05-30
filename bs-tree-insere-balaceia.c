#include "bs-tree.h"


node *Raiz;


/*----------------------------------------------------------------------------*/
/* Calcula altura da arvore                                                   */
/*----------------------------------------------------------------------------*/
int h_tree( node **n) {
	node *current =*n;
	int hl, hr;
	if ( !current ) {
		return 0;
	}
	hl =h_tree( &(current->left) );
	hr =h_tree( &(current->right) );
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
void show_tree_sem_arq( node *n, int b ) {
	int i;
	object o;
	if (n == NULL) {
		for (i = 0; i < b; i++) 
			printf("      ");
		printf("*\n"); //aponta pra NULL
		return;
	}
	show_tree_sem_arq( n->right, b+1 );
	for (i = 0; i < b; i++) 
		printf("      ");
	o =n->value;
    	printf("%d", o );
	printf("(%i)", n->balance );
	printf("\n");

	show_tree_sem_arq( n->left, b+1 );
}

void show_tree_sem_arq1( node *n,int b ) {
	printf("-------------------------------------------------------------------------------------------------\n");
	show_tree_sem_arq (n, b);
	printf("-------------------------------------------------------------------------------------------------\n");
}


/*----------------------------------------------------------------------------*/
/* Faz a compraracao entre dois objects                                       */
/*----------------------------------------------------------------------------*/
int objectcmp( object *o1, object *o2 ) {
  return *o1 < *o2 ? -1 : *o1 > *o2 ? 1 : 0;
}


/*----------------------------------------------------------------------------*/
/* Cria e aloca um novo no                                                    */
/*----------------------------------------------------------------------------*/
node *create_node( node **n) {
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
/* Rotaciona o node para a esquerda                                           */
/*----------------------------------------------------------------------------*/
void rotation_left( node **n) {

	node *a = *n;
	node *b = (*n)->right;

	a->right = b->left;
	b->left = a;

	(*n) = b;

}

/*----------------------------------------------------------------------------*/
/* Rotaciona o node para a direita                                            */
/*----------------------------------------------------------------------------*/
void rotation_right( node **n) {

	node *a = *n;
	node *b = (*n)->left;

	a->left = b->right;
	b->right = a;

	(*n) = b;

}


/*----------------------------------------------------------------------------*/
/* Conta Node                                                                 */
/*----------------------------------------------------------------------------*/
int conta_node( node **n) {
	int conta = 0 ;
	node *current = *n;
	if ( !current ) return 0;
	conta = 1 + conta_node( &(current->left) ) + conta_node( &(current->right) ); 
	return conta;
}


/*----------------------------------------------------------------------------*/
/* Insere um node na arvore                                                   */
/*----------------------------------------------------------------------------*/
int insert_node_r( node **n, object *o) {
	// curret =enderco de uma estrutura de um ponteiro node
	node *current = *n;
	// Se nao tem curret alocado, cria um node  (BASE)
	if( !current ) {
		// Se nao conseguir criar um novo node
		if( !(current = create_node( &current ) ) ) 
            return 0;
		current->value = *o;
		*n = current;
		return 1;
	// Senao compara o objeto com o objeto do valor que tem na arvore
	} else if( objectcmp( o, &current->value ) == -1 ) {
		if( insert_node_r( &(current->left ), o ) == 1){
			current->balance++;
			return 1;
		}
	} else if( objectcmp( o, &current->value ) == 1 ) {
		if( insert_node_r( &(current->right ), o) == 1){
			current->balance--;
			return 1;
		}
	}
	return 0;
}
int insert_node( node **n, object *o) {
	// curret =enderco de uma estrutura de um ponteiro node
	if ( !Raiz ) {
		// Se nao conseguir criar um novo node
		if( !(Raiz = create_node( &Raiz ) ) ) 
			return 0;
		Raiz->value = *o;
		return 1;
	}
	if ( !(insert_node_r( n, o ) ) )
		return 0;
	return 1;
}


/*----------------------------------------------------------------------------*/
/* Particonamento da Arvore                                                   */
/*----------------------------------------------------------------------------*/
node *particao_arv_teste( node **n, int k ){
	node *current = *n;
	int t = conta_node ( &(current->left) ),
  	l = conta_node ( &(current->right) );
	if ( t+1 == k) {
		return current;
	}
	if ( k <= t) {
		current->left = particao_arv_teste( &(current->left), k );
		rotation_right( &current );
		return current;
	}
	current->right = particao_arv_teste( &(current->right), k - t - 1);
	rotation_left( &current );
	return current;
}


node *particao_arv_r( node **n, int k ){
  	int t, l;
	node *current = *n;
  	t = conta_node ( &(current->left) );
  	if( t > k ) {
     	current->left = particao_arv_r( &(current->left), k );
		rotation_right( &current );
  	} 
  	if( t < k ) {
     	current->right = particao_arv_r( &(current->right), k -t -1 );
 		rotation_left( &current );
  	} 
  	return current;
}

node *particao( node **n, int k ){
	node *current = *n;
  	if( (conta_node( &current )) <= k ) {
    		return current;
	}
  	else {
    		return particao_arv_teste( &current, k );
	}
}


/*----------------------------------------------------------------------------*/
/* Arruma Arvore                                                              */
/*----------------------------------------------------------------------------*/
node	*arruma_arvore_r (node **n ) {
	node *current = *n;
	int qtd_nl = conta_node ( &(current->left) )/2, 
	    qtd_nr = conta_node ( &(current->right) )/2; 
	if ( !current )
		return NULL;	
	if ( qtd_nl > 0 ) {
		current->left = particao( &(current->left), qtd_nl );
	}
	if (qtd_nr > 0 ) {
		current->right = particao( &(current->right), qtd_nr );
	}
	return current;
}


node *arruma_arvore () {
	node *l =Raiz->left, 
		*r =Raiz->right;
	int qtd_n = conta_node ( &Raiz )/2;
 	Raiz = particao( &Raiz, qtd_n );
	Raiz->left = arruma_arvore_r ( &(Raiz->left) );
	Raiz->right = arruma_arvore_r ( &(Raiz->right) );
	return Raiz;
}

main () {
	char choose;
	int control, altura;
	object valor;
	Raiz = NULL;
	// Enquanto nao acabar o arquivo de leitura
	while ( control ) {
		printf("\nIniciando nova secao\n");
		scanf("%c", &choose );
		switch ( choose ) {
		case 'i': printf("++ insercao\n");
				scanf("%d", &valor );
				printf("%d\n", valor );
				insert_node( &Raiz, &valor );
			break;
		case 'b': printf("++ busca\n");
				scanf("%d", &valor);
				printf("%d\n", valor);
			break;
		case 'r': printf("++ remocao\n");
				scanf("%d", &valor);
				printf("%d\n", valor);
			break;
		default:	printf("++ nada\n");
				printf("Finalizando o Programa\n");
		 		control =0;
			break;
		}
		// Enquanto nao chegar no final da linha do arquivo lido
		while (choose != 10) {
			scanf("%c", &choose );
		}
		altura = h_tree( &Raiz );
 		show_tree_sem_arq1 ( Raiz, altura );
	}
	Raiz = arruma_arvore ();
	printf("arvore final \n");
	altura = h_tree( &Raiz );
 	show_tree_sem_arq1 ( Raiz, altura );
}
