#include <stdio.h>
#include <stdlib.h>

//This prog teachs how to use structs of Stacks in c

//Main struct of all structs

typedef struct no
{
	struct no * next;
	int n;
}NODE;

//auxiliar functions
NODE * cria_no(int n);
void print_no(NODE * l);

//stacks progs
NODE * insert_pilha (NODE * p,int n);
NODE * delete_pilha (NODE * p);

int main (){
	int n,i;

	NODE * pilha = NULL;

	while(scanf("%d",&n)!=EOF){
		pilha = insert_lista (pilha,n);
		getchar();
	}

	printf("Numeros inseridos\n");
	print_no(pilha);

	
	while(scanf("%d",&n)!=EOF){
		lista = delete_pilha (lista,n);
		print_no(pilha);
	}
	return 0;
}


NODE * cria_no(int n){
	NODE * new = malloc(sizeof(NODE));
	if (new!= NULL){
		new->next = NULL;
		new->n = n;
		return new;
	}
	exit(1);
}

void print_no(NODE * l){
	if (l !=NULL){
		printf("%d ",l->n );
		print_no(l->next);
	}else {
		printf("\n");
	}
}


///***PILHA*****

NODE * insert_pilha (NODE * p,int n){
	if (p == NULL) return cria_no(n);
	else{
		NODE * aux = cria_no(n);
		aux->next = p;
		return aux;
	}
}
NODE * delete_pilha (NODE * p){
	if (p!=NULL){
		NODE * aux = p;
		p = p->next;
		free(aux);
	}
}
