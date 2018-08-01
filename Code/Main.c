#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_CHAR 122

int read_cmd (char* cmd, int max);
void print_dir (char* dir, char* user);

int main (void) {
    
    char cmd[N_CHAR];
    char user[N_CHAR] = "claudio";
    char dir[N_CHAR] = "/";
    
    int retVal;
    
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
                // touch ();
                printf ("Funcao ainda nao implementada\n");
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
    
    int retVal = -1;
    
    if (!strcmp (cmd, "cd"))
        retVal = 0;
    else if (!strcmp (cmd, "mkdir"))
        retVal = 1;
    else if (!strcmp (cmd, "tree"))
        retVal = 2;
    else if (!strcmp (cmd, "touch"))
        retVal = 3;
    else if (!strcmp (cmd, "pwd"))
        retVal = 4;
    else if (!strcmp (cmd, "exit"))
        retVal = 5;
    
    return retVal;
}

void print_dir (char* dir, char* user) {
    printf ("%s %s$ ", dir, user);
}