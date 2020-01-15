// Copyright 2019 Pescaru Tudor Mihai 315CA

#include <stdio.h>
#include <stdlib.h>

#include "task1.h"
#include "task2.h"
#include "task3.h"

int main() {
    int n, *mi, i, j;
    char **byte_map;
    printf("task 1\n");
    scanf("%d", &n);
    // Alocarea si citirea vectorului cu dimensiunile fiecarei linii
    mi = (int *)malloc(n * sizeof(int));
    // Alocarea matricei de char-uri in care se vor stoca bytes-ii
    byte_map = (char **)malloc(n * sizeof(char*));
    for (i = 0; i < n; i++) {
        scanf("%d", &mi[i]);
        byte_map[i] = (char *)malloc(mi[i] * sizeof(int) * sizeof(char));
        // Citirea byte cu byte a elementelor
        for (j = 0; j < mi[i] * 4; j += 4) {
            scanf("%x", (unsigned int *)&byte_map[i][j]);
        }
    }
    // Apelarea functiei ce realizeaza task-ul 1
    task1(n, mi, byte_map);
    printf("task 2\n");
    // Apelarea functiei ce realizeaza task-ul 2
    task2(n, mi, byte_map);
    printf("task 3\n");
    // Apelarea functiei ce realizeaza task-ul 3
    task3(n, mi, byte_map);
    // Eliberarea memoriei alocate vectorului de dimensiuni
    free(mi);
    // Eliberarea memoriei alocate matricei
    for (i = 0; i < n; i++) {
        free(byte_map[i]);
    }
    free(byte_map);
    return 0;
}
