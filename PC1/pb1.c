// Copyright 2019 Pescaru Tudor Mihai

#include <stdio.h>

int main() {
    long S = 0, xmax_impar = 0, xmin_par = 9999999, N;
    long x_i, x_i_anterior, x_i_urmator;
    int nr_copaci_spec = 0, i, min_change = 0, max_change = 0;
    double m_a = 0;
    scanf("%ld", &N);
    // Testare pentru numarul minim de copaci
    if (N >= 3) {
        // Citirea inaltimilor primilor doi copaci
        scanf("%ld %ld", &x_i_anterior, &x_i);
        i = 2;
        while (i < N) {
            // Citirea inaltimii celui de-al treilea copac
            scanf("%ld", &x_i_urmator);
            // Testare copac special
            if (x_i > x_i_anterior && x_i > x_i_urmator) {
                S += x_i;
                nr_copaci_spec++;
                m_a = (m_a * (nr_copaci_spec - 1) + x_i) / nr_copaci_spec;
                // Verificarea existentei minimului si maximului
                if ((i - 1) % 2 == 0) {
                    if (x_i < xmin_par) {
                        xmin_par = x_i;
                        min_change = 1;
                    }
                } else if (x_i > xmax_impar) {
                    xmax_impar = x_i;
                    max_change = 1;
                }
            }
            // Schimbarea valorilor pentru verificarea urmatorului copac
            x_i_anterior = x_i;
            x_i = x_i_urmator;
            i++;
        }
        // Afisarea de -1 in cazul inexistentei minimului sau maximului
        if (min_change == 0) {
            xmin_par = -1;
        }
        if (max_change == 0) {
            xmax_impar = -1;
        }
    } else {
        // Toate variabilele iau valoarea 0 cand nu exista copaci speciali
        xmin_par = 0;
    }
    printf("%ld\n%.8f\n%ld\n%ld\n", S, m_a, xmax_impar, xmin_par);
    return 0;
}
