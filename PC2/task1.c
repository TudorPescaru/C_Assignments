// Copyright 2019 Pescaru Tudor Mihai 315CA

#include <stdio.h>
#include <stdlib.h>

#include "task1.h"

void task1(int n, int *mi, char **byte_map) {
    int i, j, k, byte_sum = 0, byte_count = 0;
    double average;
    // Parcurgerea elementelor de pe prima linie
    for (i = 0; i < mi[0] * 4; i++) {
        byte_sum += byte_map[0][i];
        byte_count++;
    }
    // Parcurgerea elementelor de pe ultima linie
    for (i = 0; i < mi[n - 1] * 4; i++) {
        byte_sum += byte_map[n - 1][i];
        byte_count++;
    }
    // Parcurgerea elementelor de pe prima, respectiv ultima pozitite a
    // fiecarei linii
    for (i = 1; i < n - 1; i++) {
        byte_sum += byte_map[i][0] + byte_map[i][mi[i] * 4 - 1];
        byte_count += 2;
    }
    // Calcularea mediei si afisarea acesteia
    average = (double)byte_sum / byte_count;
    printf("%.8f\n", average);
}
