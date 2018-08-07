/* arvv.h */
/* TAD ArvVar*/

/* Tipo exportado */
typedef struct arvvar ArvVar;

/* Fun��es */
ArvVar* arvv_cria (char* c, int arquivo, int nivel);

void arvv_insere (ArvVar* a, ArvVar* sa);

void arvv_imprime (ArvVar* a);

int arvv_pertence (ArvVar* a, char* c);

void arvv_libera (ArvVar* a);

//Retorna o endereço do diretorio pai do no passado como argumento.
ArvVar* arv_parent(ArvVar* a);

//Retorna a informação guardada no nó.
char* arv_info(ArvVar* a);

//Retorna o endereço o subdiretorio requisitado através do ponteiro de char.
ArvVar* arv_subdiretorio(ArvVar* a, char* c);

//Imprime a arvore de diretorios e arquivos.
void arvv_tree(ArvVar* a);
