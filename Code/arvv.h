/* arvv.h */
/* TAD ArvVar*/

/* Tipo exportado */
typedef struct arvvar ArvVar;

/* Funções */
ArvVar* arvv_cria (char c);

void arvv_insere (ArvVar* a, ArvVar* sa);

void arvv_imprime (ArvVar* a);

int arvv_pertence (ArvVar* a, char c);

void arvv_libera (ArvVar* a);


