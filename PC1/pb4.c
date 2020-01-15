// Copyright 2019 Pescaru Tudor Mihai

#include <stdio.h>

#define NMAX 100

// Se stocheaza intr-o matrice pe cate o linie fiecare regula pentru linii

void line_mat(int line[][NMAX], int N) {
    int i = 0, j, k;
    while (i < N) {
        j = 0;
        scanf("%d", &line[i][j]);
        k = 0;
        while (k < line[i][0]) {
            j++;
            scanf("%d", &line[i][j]);
            k++;
        }
        i++;
    }
}

// Se stocheaza intr-o matrice pe cate o linie fiecare regula pentru coloane

void column_mat(int column[][NMAX], int M) {
    int i = 0, j, k;
    while (i < M) {
        j = 0;
        scanf("%d", &column[i][j]);
        k = 0;
        while (k < column[i][0]) {
            j++;
            scanf("%d", &column[i][j]);
            k++;
        }
        i++;
    }
}

// Se citeste matricea ce trebuie verificata

void cit_mat(int grid[][NMAX], int N, int M) {
    int j, k;
    for (j = 0; j < N; j++) {
        for (k = 0; k < M; k++) {
            scanf("%d", &grid[j][k]);
        }
    }
}

// Se verifica daca linia curenta din matricea data respecta regulile

int line_check(int grid[][NMAX], int line[][NMAX], int M, int i) {
    int j = 0, k = 1, l;
    while (j < M && k <= line[i][0]) {
        if (grid[i][j] == 0) {
            j++;
        } else {;
            for (l = 0; l < line[i][k]; l++) {
                if (grid[i][j] == 0) {
                    return 0;
                }
                j++;
            }
            k++;
        }
    }
    if (k > line[i][0]) {
        while (j < M) {
            if (grid[i][j] == 1) {
                return 0;
            }
            j++;
        }
        return 1;
    } else {
        return 0;
    }
}

// Se verifica daca coloana curenta din matricea data respecta regulile

int column_check(int grid[][NMAX], int column[][NMAX], int N, int i) {
    int j = 0, k = 1, l;
    while (j < N && k <= column[i][0]) {
        if (grid[j][i] == 0) {
            j++;
        } else {
            for (l = 0; l < column[i][k]; l++) {
                if (grid[j][i] == 0) {
                    return 0;
                }
                j++;
            }
            k++;
        }
    }
    if (k > column[i][0]) {
        while (j < N) {
            if (grid[j][i] == 1) {
                return 0;
            }
            j++;
        }
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int N, M, T;
    int line_ok = 1, column_ok = 1;
    int i = 0, j;
    // Se citeste numarul de exercitii ce vor fi date
    scanf("%d", &T);
    while (i < T) {
        // Se citesc dimensiunile fiecarei matrici
        scanf("%d %d", &N, &M);
        int grid[NMAX][NMAX], line[NMAX][NMAX], column[NMAX][NMAX];
        // Se citesc matricile de reguli si matricea ce trebuie verificata
        line_mat(line, N);
        column_mat(column, M);
        cit_mat(grid, N, M);
        line_ok = 1;
        column_ok = 1;
        // Pentru fiecare linie se verifica daca se respecta regulile
        for (j = 0; j < N; j++) {
            line_ok = line_check(grid, line, M, j);
            if (line_ok == 0) {
                break;
            }
        }
        // Pentru fiecare coloana se verifica daca se respecta regulile
        for (j = 0; j < M; j++) {
            column_ok = column_check(grid, column, N, j);
            if (column_ok == 0) {
                break;
            }
        }
        // Se afiseaza rezultatul fiecarei verificari
        if (line_ok == 1 && column_ok == 1) {
            printf("Corect\n");
        } else {
            printf("Eroare\n");
        }
        i++;
    }
    return 0;
}
