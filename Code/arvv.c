/* arvv.c */

#include <stdio.h>
#include <stdlib.h>
#include "arvv.h"
#include <string.h>

#define N_MAX 122

struct arvvar {
	char info[N_MAX];
	int arquivo;
	struct arvvar* prim; /* ponteiro para eventual primeiro filho */
	struct arvvar* prox; /* ponteiro para eventual irm�o */
};

/* Fun��o cria
** Cria uma folha isolada para guardar um caractere e retorna seu ponteiro
*/
ArvVar* arvv_cria (char c) {
	ArvVar *a = (ArvVar*) malloc(sizeof(ArvVar));
	a->info = c;
	a->prim = NULL;
	a->prox = NULL;
	return a;
}

/* Fun��o insere
** Insere um n� pr�-existente na (sub)�rvore 'a'
*/
void arvv_insere (ArvVar* a, ArvVar* sa) {
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
	if (strcmp(a->info, c))
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
