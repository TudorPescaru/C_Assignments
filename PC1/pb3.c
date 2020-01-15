// Copyright 2019 Pescaru Tudor Mihai

#include <stdio.h>

#define NMAX 100

// Se sorteaza vectorul de credite si cel de note

void credit_sort(int x[], int c[], int n) {
    int i, aux, j;
    for (i = 0; i < n - 1; i++) {
        for (j = i+1; j < n; j++) {
            if ((10 - x[i]) * c[i] < (10 - x[j]) * c[j]) {
                aux = c[i];
                c[i] = c[j];
                c[j] = aux;
                aux = x[i];
                x[i] = x[j];
                x[j] = aux;
            }
        }
    }
}

int main() {
    int n, x[NMAX], c[NMAX], i, P = 0, m = 0, p_min;
    scanf("%d", &n);
    // Se adauga in vector notele de la fiecare materie
    for (i = 0; i < n; i++) {
        scanf("%d", &x[i]);
    }
    // Se adauga in vector numarul de credite respectiv fiecarei materii
    for (i = 0; i < n; i++) {
        scanf("%d", &c[i]);
    }
    scanf("%d", &p_min);
    credit_sort(x, c, n);
    // Se calculeaza numarul total curent de puncte
    for (i = 0; i < n; i++) {
        P = P + x[i] * c[i];
    }
    // Se majoreaza progresiv la 10 notele pana la obtinerea punctajului minim
    for (i = 0; i < n && P < p_min; i++) {
        if (x[i] != 10) {
            P = P + c[i] * (10 - x[i]);
            m++;
        }
    }
    // In cazul in care nu se poate obtine punctajul minim se afiseaza -1
    if (P < p_min) {
        m = -1;
    }
    // Se afiseaza numarul minim de note majorate
    printf("%d", m);
    return 0;
}
