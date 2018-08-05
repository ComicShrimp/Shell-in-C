#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvv.h"

#define N_CHAR 122
#define ARQ 1
#define DIR 0

int read_cmd (char* cmd, int max);
void print_dir (char* dir, char* user);

int main (void) {

    char aux[N_CHAR];
    char cmd[N_CHAR];
    char user[N_CHAR] = "claudio";
    char dir[N_CHAR] = "/";

    int retVal, i, j;

    ArvVar* fs = arvv_cria("/", DIR);

    // loop principal
    do {
        print_dir (dir, user);
        retVal = read_cmd (cmd, N_CHAR);
        switch (retVal) {
            case 0:
                // cd ();
                printf ("Funcao ainda nao implementada\n");
                break;
            case 1:
                // mkdir ();
                printf ("Funcao ainda nao implementada\n");
                break;
            case 2:
                // touch ()
                j = 0;
                for(i = 6;i < strlen(cmd);i++){
                    aux[j] = cmd[i];
                    j++;
                }

                ArvVar* auxi = arvv_cria(aux, ARQ);
                arvv_insere(fs, auxi);

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
      comando[i] = cmd[i];
      if(cmd[i + 1] == ' '){
          break;
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
