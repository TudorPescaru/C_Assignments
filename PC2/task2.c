// Copyright 2019 Pescaru Tudor Mihai 315CA

#include <stdio.h>
#include <stdlib.h>

#include "task2.h"

void task2(int n, int *mi, char **byte_map) {
    int k, i, j, l, x, val, byte_increment, aux, m, poz;
    long li, ind, new_size;
    char op, dim, byte[4];
    // Citirea numarului de operatii
    scanf("%d", &k);
    for (l = 1; l <= k; l++) {
        // Citirea operatiei, tipului de date, a liniei si a indexului
        scanf(" %c", &op);
        scanf(" %c", &dim);
        scanf("%ld %ld", &li, &ind);
        // Determinarea numarului de bytes corespunzator fiecarui tip de date
        if (dim == 'C') {
            byte_increment = sizeof(char);
        } else {
            if (dim == 'S') {
                byte_increment = sizeof(short);
            } else {
                byte_increment = sizeof(int);
            }
        }
        // Operatia de modify
        if (op == 'M') {
            // Citirea noi valori
            scanf("%x", &val);
            // Convertirea valori in format byte-cu-byte
            for (i = 3; i >= 0; i--) {
                byte[i] = val >> 24;
                val = val << 8;
            }
            // Tranformarea indicelui de la tipul de date la cel pe bytes
            ind = (ind - 1) * byte_increment;
            poz = mi[li] * 4;
            // Realocarea dimensiunii unei linii in cazul adaugarii de valori
            if (ind >= mi[li] * 4) {
                mi[li] = (ind + 4 - ind % 4) / 4;
                new_size = mi[li] * sizeof(int);
                byte_map[li] = (char *)realloc(byte_map[li], new_size);
            }
            // Umplerea cu 0 de la ultima valoarea pana la cea noua
            for (i = poz; i < ind; i++) {
                byte_map[li][i] = 0;
            }
            // Adaugarea fiecarui byte din valoarea noua in matrice
            for (i = ind; i < ind + byte_increment; i++) {
                byte_map[li][i] = byte[i - ind];
            }
        } else {
            // Operatia de delete
            if (op == 'D') {
                // Tranformarea indicelui de la tipul de date la cel pe bytes
                ind = (ind - 1) * byte_increment;
                for (i = ind; i < ind + byte_increment; i++) {
                    byte_map[li][i] = 0;
                }
            } else {
                // Operatia de swap
                if (op == 'S') {
                    // Tranformarea indicelui de la tipul de date la cel pe
                    // bytes
                    ind = ind * byte_increment;
                    // Inversarea in cazul unui integer
                    if (byte_increment == 4) {
                        aux = byte_map[li][ind + 3];
                        byte_map[li][ind + 3] = byte_map[li][ind];
                        byte_map[li][ind] = aux;
                        aux = byte_map[li][ind + 2];
                        byte_map[li][ind + 2] = byte_map[li][ind + 1];
                        byte_map[li][ind + 1] = aux;
                    } else {
                        // Inversarea in cazul unui short
                        if (byte_increment == 2) {
                            aux = byte_map[li][ind + 1];
                            byte_map[li][ind + 1] = byte_map[li][ind];
                            byte_map[li][ind] = aux;
                        }
                    }
                }
            }
        }
    }
    // Afisarea matricei in format de 4 bytes pentru fiecare valoare
    for (i = 0; i < n; i++) {
        for (j = 0; j < mi[i]; j++) {
            for (m = 3; m >= 0 ; m--) {
                printf("%02X", byte_map[i][j * 4 + m] & 0xFF);
            }
            printf(" ");
        }
        printf("\n");
    }
}
