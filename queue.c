#include <stdio.h>
#include <stdlib.h>

//This prog teachs how to use structs of Queue in c

//Main struct of all structs

typedef struct no
{
	struct no * next;
	int n;
}NODE;


//expecific struct used in queue programs
typedef struct fila
{
	NODE * begin,*final;
}FILA;

//auxiliar functions
NODE * cria_no(int n);
void print_no(NODE * l);

//Queue progs
FILA * cria_fila(void);
FILA * insert_fila(FILA * f,int n);
FILA * delete_fila (FILA * f);


int main (){
	int n,i;
	FILA * fila = cria_fila();
	while(scanf("%d",&n)!=EOF){
		fila = insert_fila(fila,n);
	}

	printf("OK\n");
	while(scanf("%d",&n)!=EOF){
		delete_fila(fila);
		print_no(fila->begin);
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
///***FILAS*****

FILA * cria_fila(void){
	FILA * f = malloc(sizeof(FILA));
	if (f!=NULL){
		f->begin = f->final = NULL;
		return f;
	}
	exit(1);
}

FILA * insert_fila(FILA * f,int n){
	if (f->begin == NULL){
		f->begin = f->final = cria_no(n);
	}else{
		NODE * aux = cria_no(n);
		aux->next = f->begin;
		f->begin = aux;
	}
	return f;
}

FILA * delete_fila (FILA * f) {
	if (f->begin == NULL) return f;
	else{
		if (f->begin == f->final){
			NODE * aux = f->begin;
			f->begin = f->final = NULL;
			free(aux);
		}else{
			NODE * aux = f->begin;
			while(aux->next!=f->final){
				aux = aux->next; 
			}
			f->final = aux;
			aux = aux->next;
			free(aux);
			f->final->next = NULL;
		}
	}
	return f;
}
