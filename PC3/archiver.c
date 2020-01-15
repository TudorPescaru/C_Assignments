// Copyright 2019 Pescaru Tudor Mihai 315CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "create.h"
#include "list.h"
#include "extract.h"

int main() {
    // Initializarea uniunii pentru header
    union record tar;
    while (1) {
        // Citirea fiecarei comenzi
        char s[512];
        fgets(s, 512, stdin);
        if (strcmp(s, "\n") != 0) {
            s[strlen(s) - 1] = '\0';
        }
        // Comanda create
        char *command = strtok(s, " ");
        if (strcmp(command, "create") == 0) {
            // Verificarea existentei argumentelor necesare
            char *archive_name = strtok(NULL, " ");
            char *dir_name = strtok(NULL, " ");
            if (archive_name == NULL || dir_name == NULL) {
                printf("> Wrong commmand!\n");
            } else {
                // Apelarea functiei pentru task-ul create
                create(tar, archive_name, dir_name);
            }
        } else {
            // Comanda list
            if (strcmp(command, "list") == 0) {
                // Verificarea existentei argumentului necesar
                char *archive_name = strtok(NULL, " ");
                if (archive_name == NULL) {
                    printf("> Wrong commmand!\n");
                } else {
                    // Apelarea functiei pentru task-ul list
                    list(archive_name);
                }
            } else {
                // Comanda extract
                if (strcmp(command, "extract") == 0) {
                    // Verificarea existentei argumentelor necesare
                    char *file_name = strtok(NULL, " ");
                    char *archive_name = strtok(NULL, " ");
                    if (file_name == NULL || archive_name == NULL) {
                        printf("> Wrong commmand!\n");
                    } else {
                        // Apelarea functiei pentru task-ul extract
                        extract(file_name, archive_name);
                    }
                } else {
                    // Comanda exit
                    if (strcmp(command, "exit") == 0) {
                        return 0;
                    } else {
                        // Afisarea in cazul unei comenzi gresite/inexistente
                        printf("> Wrong commmand!\n");
                    }
                }
            }
        }
    }
}
