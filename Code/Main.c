#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvv.h"

#define N_CHAR 122
#define ARQ 1
#define DIR 0

char* argumento(char* c, int ini);
int read_cmd (char* cmd, int max);
void print_dir (char* dir, char* user);

char ax[N_CHAR];

int main (void) {

    char aux[N_CHAR];
    char cmd[N_CHAR];
    char user[N_CHAR] = "claudio";
    char dir[N_CHAR] = "/";

    ArvVar* auxi;

    int retVal;

    ArvVar* atual = arvv_cria(dir, DIR);
    ArvVar* parent = arv_parent(atual);

    // loop principal
    do {
        memset(ax, 0, sizeof(ax));
        memset(aux, 0, sizeof(aux));

        print_dir (dir, user);
        retVal = read_cmd (cmd, N_CHAR);
        switch (retVal) {
            case 0:
                // cd ();

                if(strlen(cmd) < 4){
                    printf("Esse comando deve receber arguementos\n");
                    break;
                }

                strcpy(aux, argumento(cmd, 3));

                if(!strcmp(aux, "..")){
                    if(parent == NULL){
                        printf("Voce ja esta no diretorio raiz\n");
                    }else{
                        atual = parent;
                        parent = arv_parent(atual);
                    }
                }else{
                    auxi = arv_subdiretorio(atual, aux);
                    if(auxi == NULL){
                        printf("Diretorio não existe.\n");
                    }else{
                        atual = auxi;
                        parent = arv_parent(atual);
                    }
                }

                strcpy(dir, arv_info(atual));

                break;

            case 1:
                // mkdir ();
                //Tentar implementar igual ao linux onde cada barra é um
                //subdiretorio
                if(strlen(cmd) < 7){
                    printf("Esse comando deve receber arguementos\n");
                    break;
                }

                strcpy(aux, argumento(cmd, 6));

                auxi = arvv_cria(aux, DIR);
                arvv_insere(atual, auxi);

                break;

            case 2:
                // touch ()
                if(strlen(cmd) < 7){
                    printf("Esse comando deve receber arguementos\n");
                    break;
                }

                strcpy(aux, argumento(cmd, 6));

                auxi = arvv_cria(aux, ARQ);
                arvv_insere(atual, auxi);

                printf ("Arquivo Criado.\n");
                break;

            case 3:
                // tree ();
                printf ("Funcao ainda nao implementada\n");
                break;
            case 4:
                // pwd ();
                printf ("Funcao ainda nao implementada\n");
                break;
            case 5:
                // exit ();
                break;
            default:
                printf ("\rComando não encontrado\n");
        }
    } while (retVal != 5);

    return 0;
}

int read_cmd (char* cmd, int max) {
    fflush (stdin);
    fgets (cmd, max, stdin);
    cmd[strlen(cmd)-1] = '\0';

    char comando[6];

    int i;
    for(i = 0;i < strlen(cmd);i++){
      if(cmd[i] == ' '){
          break;
      }else if(cmd[3] == '.' && cmd[4] == '.'){
          strcpy(comando, "cd");
          break;
      }else{
          comando[i] = cmd[i];
      }
    }

    int retVal = -1;

    if (!strcmp (comando, "cd"))
        retVal = 0;
    else if (!strcmp (comando, "mkdir"))
        retVal = 1;
    else if (!strcmp (comando, "touch"))
        retVal = 2;
    else if (!strcmp (comando, "tree"))
        retVal = 3;
    else if (!strcmp (comando, "pwd"))
        retVal = 4;
    else if (!strcmp (comando, "exit"))
        retVal = 5;

    return retVal;
}

void print_dir (char* dir, char* user) {
    printf ("%s %s$ ", dir, user);
}

char* argumento(char* c, int ini){
    int j = 0;
    int i;

    for(i = ini;i < strlen(c);i++){
        ax[j] = c[i];
        j++;
    }

    return ax;
}
