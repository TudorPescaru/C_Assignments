// Copyright 2019 Pescaru Tudor Mihai

#include <stdio.h>

#define NMAX 100

// Functia descresc creeaza numarul format cu cifrele in ordine descrescatoare

long descresc(long N) {
    int ap[10], i, c, j;
    long nr_descrescator = 0;
    for (i = 0; i <= 9; i++) {
        ap[i] = 0;
    }
    while (N != 0) {
        c = N % 10;
        ap[c]++;
        N = N/10;
    }
    for (i = 9; i >= 0; i--) {
        for (j = 1; j <= ap[i]; j++) {
            nr_descrescator = nr_descrescator * 10 + i;
        }
    }
    return nr_descrescator;
}

// Functia cresc creeaza numarul format cu cifrele in ordine crescatoare

long cresc(long N) {
    int ap[9], i, c, j;
    long nr_crescator = 0;
    for (i = 1; i <= 9; i++) {
        ap[i] = 0;
    }
    while (N != 0) {
        c = N % 10;
        ap[c]++;
        N = N/10;
    }
    for (i = 1; i <= 9; i++) {
        for (j = 1; j <= ap[i]; j++) {
            nr_crescator = nr_crescator * 10 + i;
        }
    }
    return nr_crescator;
}

// Functia determina sfarsitul perioadei

int verificare_duplicate(long p[], int m) {
    int ok = 0, i, j;
    for (i = 0; i < m; i++) {
        for (j = i + 1; j <= m; j++) {
            if (p[i] == p[j]) {
                ok = 1;
                break;
            }
        }
    }
    return ok;
}

int main() {
    long N, n_crescator = 0, n_descrescator = 0, dif, p[NMAX];
    int k = 0, m = 0, i = 0, nr_dif = 0;
    scanf("%ld", &N);
    n_descrescator = descresc(N);
    n_crescator = cresc(N);
    // Se calculeaza numarul in urma diferentei dintre nr descresc si cel cresc
    dif = n_descrescator - n_crescator;
    p[m] = dif;
    // Pana la descoperirea finalului de perioada nr calculate se pun in vector
    while (verificare_duplicate(p, m) == 0) {
        n_descrescator = descresc(dif);
        n_crescator = cresc(dif);
        dif = n_descrescator - n_crescator;
        m++;
        p[m] = dif;
    }
    // Se calculeaza numarul de numere dinaintea inceperii perioadei
    while (p[i] != p[m]) {
        k++;
        i++;
    }
    printf("%d\n%ld ", k, p[i]);
    i++;
    // Se afiseaza numerele din perioada
    while (i < m) {
        printf("%ld ", p[i]);
        i++;
    }
    return 0;
}
