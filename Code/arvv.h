/* arvv.h */
/* TAD ArvVar*/

/* Tipo exportado */
typedef struct arvvar ArvVar;

/* Fun��es */
ArvVar* arvv_cria (char* c, int arquivo);

void arvv_insere (ArvVar* a, ArvVar* sa);

void arvv_imprime (ArvVar* a);

int arvv_pertence (ArvVar* a, char* c);

void arvv_libera (ArvVar* a);

ArvVar* arv_parent(ArvVar* a);

char* arv_info(ArvVar* a);

ArvVar* arv_subdiretorio(ArvVar* a, char* c);

void arvv_tree(ArvVar* a);
