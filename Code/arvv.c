/* arvv.c */

#include <stdio.h>
#include <stdlib.h>
#include "arvv.h"

struct arvvar {
	char info;
	struct arvvar* prim; /* ponteiro para eventual primeiro filho */
	struct arvvar* prox; /* ponteiro para eventual irmão */
};

/* Função cria
** Cria uma folha isolada para guardar um caractere e retorna seu ponteiro
*/
ArvVar* arvv_cria (char c) {
	ArvVar *a = (ArvVar*) malloc(sizeof(ArvVar));
	a->info = c;
	a->prim = NULL;
	a->prox = NULL;
	return a;
}

/* Função insere
** Insere um nó pré-existente na (sub)árvore 'a'
*/
void arvv_insere (ArvVar* a, ArvVar* sa) {
	sa->prox = a->prim;
	a->prim = sa;
}

/* Função imprime
** Percorre a árvore, imprimindo sua estrutura, seguindo a formatação textual
*/
void arvv_imprime (ArvVar* a) {
	ArvVar* p;
	printf(" <%c",a->info);
	for (p = a->prim; p != NULL; p = p->prox)
		arvv_imprime(p);
	printf(">");
}

/* Função pertence
** Percorre a árvore, buscando um valor. Retorna um inteiro (lógico) indicando se encontrou ou não
*/
int arvv_pertence (ArvVar* a, char c) {
	ArvVar* p;
	if (a->info == c)
		return 1;
	else {
		for (p = a->prim; p != NULL; p = p->prox) {
			if (arvv_pertence(p,c))
				return 1;
		}
		return 0;
	}
}


/* Função libera
** Libera a memória alocada para a árvore, nó a nó
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




