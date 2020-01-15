// Copyright 2019 Pescaru Tudor Mihai 315CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "list.h"


// Functia principala de list
void list(char *archive_name) {
    // Deschiderea fisierului arhiva pentru parcurgere
    FILE *archive;
    if ((archive = fopen(archive_name, "rt")) == NULL) {
        printf("> File not found!\n");
    } else {
        char name[100], size[12], ch;
        int i, sizei, end, j, ok;
        fseek(archive, 0, SEEK_SET);
        // Parcurgerea caracter cu caracter a arhivei
        // Pentru fiecare iteratie a while-ului se va parcurge cate un fisier
        fscanf(archive, "%c", &ch);
        while (!feof(archive)) {
            memset(name, 0, 100);
            memset(size, 0, 12);
            j = 0;
            // Determinarea numelui fiecarui fisier
            for (i = 1; i < 100; i++) {
                if (ch != 0) {
                    name[j] = ch;
                    j++;
                }
                fscanf(archive, "%c", &ch);
            }
            name[j] = '\0';
            // Determinarea finalului setului de fisiere
            if (name[0] == '\0') {
                break;
            }
            // Scrierea numelui
            printf("> %s\n", name);
            // Parcurgerea datelor pana la campul size
            for (i = 100; i < 124; i++) {
                fscanf(archive, "%c", &ch);
            }
            fscanf(archive, "%c", &ch);
            j = 0;
            ok = 0;
            // Determinarea dimensiunii fisierului curent
            for (i = 124; i < 136; i++) {
                if (ch != '0' && ok == 0) {
                    ok = 1;
                }
                if (ok == 1) {
                    size[j] = ch;
                    j++;
                }
                fscanf(archive, "%c", &ch);
            }
            size[j] = '\0';
            sizei = strtol(size, NULL, 8);
            // Parcurgerea pana la finalul header-ului
            for (i = 136; i < 512; i++) {
                fscanf(archive, "%c", &ch);
            }
            // Parcurgerea datelor fisierului curent
            end = ((sizei / 512) + 1) * 512;
            for (i = 512; i < 512 + end; i++) {
                fscanf(archive, "%c", &ch);
            }
        }
    }
    fclose(archive);
}
