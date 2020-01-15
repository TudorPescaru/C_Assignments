// Copyright 2019 Pescaru Tudor Mihai 315CA

#include <stdio.h>
#include <stdlib.h>

#include "task3.h"

// Functia recursiva ce va realiza un algoritm de fill
void black_hole(int x, int y, char **byte_map, int n, int *mi, int *size) {
    // Testarea indicelui pozitiei pentru a ne asigura ca se afla in matrice
    if (x >= 0 && x < n && y >= 0 && y < mi[x] * 4) {
        // Verificare ca byte-ul de la pozitia curenta este 0
        if (byte_map[x][y] == 0) {
            // Incrementarea dimensiunii gaurii negre
            *size += 1;
            // Marcarea byte-ului ca fiind parcurs
            byte_map[x][y] = -1;
            // Navigarea in matrice in sus
            black_hole(x + 1, y, byte_map, n, mi, size);
            // Navigarea in matrice la dreapta
            black_hole(x, y + 1, byte_map, n, mi, size);
            // Navigarea in matrice in jos
            black_hole(x - 1, y, byte_map, n, mi, size);
            // Navigarea in matrice la stanga
            black_hole(x, y - 1, byte_map, n, mi, size);
        } else {
            return;
        }
    } else {
        return;
    }
}

void task3(int n, int *mi, char **byte_map) {
    int i, j, k, l, supermasive = -1, size = 0, max = -1;
    for (k = 0; k < n; k++) {
        for (l = 0; l < mi[k] * 4; l++) {
            black_hole(k, l, byte_map, n, mi, &size);
            // Deterimnarea celei mai mari gauri negre si a pozitiei de start
            // a acesteia
            if (size > supermasive) {
                supermasive = size;
                i = k;
                j = l;
            }
            size = 0;
        }
    }
    printf("%d %d %d\n", i, j, supermasive);
}
