#include <stdio.h>
#include <stdlib.h>

//This prog teachs how to use structs of list in c

//Main struct of all structs

typedef struct no
{
	struct no * next;
	int n;
}NODE;

NODE * cria_no(int n);
void print_no(NODE * l);


//list progs
NODE * insert_lista (NODE * l,int n);
NODE * delete_lista(NODE * l,int n);

int main (){
	int n,i;

	NODE * lista = NULL;

	while(scanf("%d",&n)!=EOF){
		lista = insert_lista (lista,n);
		getchar();
	}

	printf("Numeros inseridos\n");
	print_no(lista);

	
	while(scanf("%d",&n)!=EOF){
		lista = delete_lista (lista,n);
		print_no(lista);
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

///***LISTA*****

NODE * insert_lista (NODE * l,int n){
	if (l == NULL) return cria_no(n);
	else{
		l->next = insert_lista(l->next,n);
	}
	return l;
}

NODE * delete_lista(NODE * l,int n){
	if (l == NULL) return NULL;
	else if (l->n == n){
		NODE * tmp = l;
		l = l->next;
		free(tmp);
	}else{
	 l->next = delete_lista(l->next,n);
	}
	return l;
}
