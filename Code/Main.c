#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvv.h"

#define N_CHAR 122
//Variaveis para definir se é arquivo ou diretório
#define ARQ 1
#define DIR 0

char* tira_pwd(char* c); //Função para remover o nome da ultima pasta
char* argumento(char* c, int ini); //Função que separa os argumentos do comando
int read_cmd (char* cmd, int max);
void print_dir (char* dir, char* user);

char ax[N_CHAR]; //Variavel auxiliar de propositos gerais

int main (void) {

    char pwd[N_CHAR * 5]; //Variavel para guardar contantemente o valor do comando pwd
    char aux[N_CHAR]; //Variavel auxiliar
    char cmd[N_CHAR];
    char user[N_CHAR] = "claudio";
    char dir[N_CHAR] = "/";

    ArvVar* auxi; //Variavel auxiliar para ser manipulada dentro do switch case

    int retVal;

    int nivel = 0; //Variavel para guardar o nivel atual da arvore

    ArvVar* atual = arvv_cria(dir, DIR, nivel); //Cria o diretorio raiz
    ArvVar* parent = arv_parent(atual); //Atualiza o valor do diretorio pai

    ArvVar* raiz = atual; //Guarda para sempre o valor do diretorio raiz

    // loop principal
    do {
        //Reseta todos os vetoresde char para não guardar "lixo" de usos anteriores
        memset(ax, 0, sizeof(ax));
        memset(aux, 0, sizeof(aux));
        memset(cmd, 0, sizeof(cmd));

        print_dir (dir, user);
        retVal = read_cmd (cmd, N_CHAR);
        switch (retVal) {
            case 0:
                // cd ();

                //Verifica se possui argumentos apos o comando
                if(strlen(cmd) < 4){
                    printf("Esse comando deve receber arguementos\n");
                    break;
                }

                //Chama a função argumento e copia o valor retornado para a variavel auxiliar
                strcpy(aux, argumento(cmd, 3));

                //Verifica se o comando cd .. foi dado para poder retornar para o diretorio pai
                if(!strcmp(aux, "..")){
                    if(parent == NULL){
                        printf("Voce ja esta no diretorio raiz\n");
                    }else{
                        atual = parent;
                        parent = arv_parent(atual);

                        tira_pwd(pwd);

                        //Indica que o nivel foi diminuido, pois usou-se o comando cd ..
                        nivel--;
                    }
                }else{
                    //Busca o endereço do subdiretorio
                    auxi = arv_subdiretorio(atual, aux);

                    //Verifica se o subdiretorio existe
                    if(auxi == NULL){
                        printf("Diretorio não existe.\n");
                    }else{
                        atual = auxi;
                        parent = arv_parent(atual);

                        //Adiciona o nome da pasta recem acessada à variavel do comando pwd
                        strcat(pwd, "/");
                        strcat(pwd, arv_info(atual));

                        //Indica que o nivel foi aumentado, pois usou-se o comando cd
                        nivel++;
                    }
                }

                //Copia o valor do diretorio recem entrado para a variavel dir
                strcpy(dir, arv_info(atual));

                break;

            case 1:
                // mkdir ();

                //Verifica se o comando possui argumentos
                if(strlen(cmd) < 7){
                    printf("Esse comando deve receber arguementos\n");
                    break;
                }

                //Chama a função argumento e copia para a variavel auxiliar
                strcpy(aux, argumento(cmd, 6));

                //Cria um novo nó e incrementa o valor do nivel antes de chamar a função
                // pois o diretório é criado sempre 1 nivel abaixo.
                auxi = arvv_cria(aux, DIR, nivel + 1);
                arvv_insere(atual, auxi); //Insere o nó no diretorio atual

                break;

            case 2:
                // touch ()

                //verifica se o comando possui argumentos
                if(strlen(cmd) < 7){
                    printf("Esse comando deve receber arguementos\n");
                    break;
                }

                strcpy(aux, argumento(cmd, 6));

                //Cria um novo nó e incrementa o valor do nivel antes de chamar a função
                // pois o diretório é criado sempre 1 nivel abaixo.
                auxi = arvv_cria(aux, ARQ, nivel + 1);
                arvv_insere(atual, auxi);

                break;

            case 3:
                // tree ();

                //Chama a função para imprimir valor do comando tree
                arvv_tree(raiz);
                break;
            case 4:
                // pwd ();

                //verifica se possui algo no vetor de char pwd
                if(strlen(pwd) == 0){
                    printf("/\n");
                }else{
                    printf("%s\n", pwd);
                }

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

    int i;//Variavel para laços for

    fflush (stdin);
    fgets (cmd, max, stdin);
    cmd[strlen(cmd)-1] = '\0';

    char comando[6] = "";//Variavel para guardar somente o comando

    //laço para separar o comando
    for(i = 0;i < strlen(cmd);i++){
        //Identifica o fim do comando
      if(cmd[i] == ' '){
          break;
      }else if(cmd[3] == '.' && cmd[4] == '.'){ //Verifica se o comando é cd pois
          strcpy(comando, "cd");                // com o cd .. a leitura fica errada.
          break;
      }else{
          comando[i] = cmd[i]; //Atribui o valor do cmd para o comando
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

    //Começa a copiar os valores do argumento a partir do valor passado, que identifica
    //o tamanho do comando
    for(i = ini;i < strlen(c);i++){
        ax[j] = c[i];
        j++;
    }

    return ax; //Retorna o valor conseguido no argumento
}

char* tira_pwd(char* c){
    int i;

    //Percorre o vetor de trás para frente até a /
    for(i = strlen(c) - 1;c[i] != '/';i--);
    c[i] = '\0';

    return c; //Retorna o valor atualizado
}
