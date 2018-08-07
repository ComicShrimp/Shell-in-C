/* arvv.c */

#include <stdio.h>
#include <stdlib.h>
#include "arvv.h"
#include <string.h>

#define N_MAX 122

struct arvvar {
	char info[N_MAX];
	int arquivo, nivel;
	struct arvvar* parent; // Ponteiro para o diretorio anterior
	struct arvvar* prim; /* ponteiro para eventual primeiro filho */
	struct arvvar* prox; /* ponteiro para eventual irm�o */
};

/* Fun��o cria
** Cria uma folha isolada para guardar um caractere e retorna seu ponteiro
*/
ArvVar* arvv_cria (char* c, int arquivo, int nivel) {
	ArvVar *a = (ArvVar*) malloc(sizeof(ArvVar));
	strcpy(a->info, c);
	a->prim = NULL;
	a->prox = NULL;
	a->arquivo = arquivo;
	a->parent = NULL;
	a->nivel = nivel;
	return a;
}

/* Fun��o insere
** Insere um n� pr�-existente na (sub)�rvore 'a'
*/
void arvv_insere (ArvVar* a, ArvVar* sa) {
	sa->parent = a;
	sa->prox = a->prim;
	a->prim = sa;
}

/* Fun��o imprime
** Percorre a �rvore, imprimindo sua estrutura, seguindo a formata��o textual
*/
void arvv_imprime (ArvVar* a) {
	ArvVar* p;
	printf(" <%s",a->info);
	for (p = a->prim; p != NULL; p = p->prox)
		arvv_imprime(p);
	printf(">");
}

/* Fun��o pertence
** Percorre a �rvore, buscando um valor. Retorna um inteiro (l�gico) indicando se encontrou ou n�o
*/
int arvv_pertence (ArvVar* a, char* c) {
	ArvVar* p;
	if (!strcmp(a->info, c))
		return 1;
	else {
		for (p = a->prim; p != NULL; p = p->prox) {
			if (arvv_pertence(p,c))
				return 1;
		}
		return 0;
	}
}


/* Fun��o libera
** Libera a mem�ria alocada para a �rvore, n� a n�
*/
void arvv_libera (ArvVar* a) {
	ArvVar* p = a->prim;
	while (p != NULL) {
		ArvVar* t = p->prox;
		arvv_libera(p);
		p = t;
	}
	free(a);
}

//Retorna o endereço do diretorio pai do no passado como argumento.
ArvVar* arv_parent(ArvVar* a){
	return a->parent;
}

//Retorna a informação guardada no nó.
char* arv_info(ArvVar* a){
	return a->info;
}

//Retorna o endereço o subdiretorio requisitado através do ponteiro de char.
ArvVar* arv_subdiretorio(ArvVar* a, char* c){

	ArvVar* aux;
	for(aux = a->prim;aux != NULL;aux = aux->prox){
		//Verifica se o valor passado é igual ao no avaliado, e se não é um arquivo.
		if(!strcmp(aux->info, c) && !aux->arquivo){
			return aux;
		}
	}

	//Caso nenhum no corresponda ao desejado retorna nulo.
	return NULL;
}

//Imprime a arvore de diretorios e arquivos.
void arvv_tree(ArvVar* a){

	ArvVar* p;

	int i = 0;
	//Imprime o - dependendo no nivel do diretorio ou arquivo.
	for(i = 0;i < a->nivel;i++){
		printf("-");
	}

	//Imprime a informação, no caso o nome, do diretoro ou arquivo
	printf("%s",a->info);
	printf("\n");

	//Chama o arvv_tree para todas as subarvores do nó.
	for(p = a->prim; p != NULL; p = p->prox){
		arvv_tree(p);
	}
}
