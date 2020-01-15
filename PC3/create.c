// Copyright 2019 Pescaru Tudor Mihai 315CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "create.h"

// Functia ce realizeaza calculul checksum-ului
void calcchk(union record *tar) {
    memset((*tar).header.chksum, ' ', 8);
    unsigned int checksum = 0;
    int offset;
    char tochar[8];
    // Parcurgerea tuturor octetilor din header
    for (int i = 0; i < 512; i++) {
        checksum += (unsigned char)(*tar).charptr[i];
    }
    sprintf(tochar, "%o", checksum);
    offset = sizeof((*tar).header.chksum) - strlen(tochar) - 2;
    // Memorarea checksum-ului in header
    memset((*tar).header.chksum, '0', offset);
    memcpy((*tar).header.chksum + offset, tochar, strlen(tochar));
    (*tar).header.chksum[6] = '\0';
    (*tar).header.chksum[7] = ' ';
}

// Functia ce prelucreaza informatiile din usermap.txt
void readuser(FILE *user, union record *tar) {
    int ok = 0, isok = 1, offset;
    unsigned int toint;
    char line[512], tochar[8], *p;
    // Determinarea liniei pe care se afla username-ul cautat
    while (ok != 1 && fgets(line, 512, user) != NULL) {
        p = strstr(line, (*tar).header.uname);
        if (p != NULL) {
            ok = 1;
        }
    }
    p = strtok(line, ":");
    while (p != NULL) {
        // Determinarea uid-ului
        if (isok == 3) {
            toint = atoi(p);
            sprintf(tochar, "%o", toint);
            offset = sizeof((*tar).header.uid) - strlen(tochar) - 1;
            memset((*tar).header.uid, '0', offset);
            memcpy((*tar).header.uid + offset, tochar, strlen(tochar));
        }
        // Determinarea gid-ului
        if (isok == 4) {
            toint = atoi(p);
            sprintf(tochar, "%o", toint);
            offset = sizeof((*tar).header.gid) - strlen(tochar) - 1;
            memset((*tar).header.gid, '0', offset);
            memcpy((*tar).header.gid + offset, tochar, strlen(tochar));
        }
        p = strtok(NULL, ":");
        isok++;
    }
}

// Functia ce citeste continutul fiecarui fisier ce trebuie arhivat
void readcontent(FILE *f, FILE *archive, int *size) {
    char ch;
    int i;
    for (i = 0; i < (*size); i++) {
        fscanf(f, "%c", &ch);
        fprintf(archive, "%c", ch);
    }
    // Calcularea numarului de octeti de 0 ce trebuie pusi pana la o dimensiune
    // divizibila cu 512
    if ((*size) % 512 != 0) {
        (*size) = ((((*size) / 512) + 1) * 512) - (*size);
        ch = 0;
        for (i = 0; i < (*size); i++) {
            fprintf(archive, "%c", ch);
        }
    }
}

// Functia ce calculeaza field-ul mode in functie de permisiunile fisierelor
void permisions(union record *tar, char *c) {
    int permision = 0, oct = 0, offset, i;
    char tochar[4];
    for (i = 0; i < strlen(c); i++) {
        if (c[i] == '-') {
            oct += 0;
        }
        // Permisiunea execute
        if (c[i] == 'x') {
            oct += 1;
        }
        // Permisiunea write
        if (c[i] == 'w') {
            oct += 2;
        }
        // Permisiunea read
        if (c[i] == 'r') {
            oct += 4;
        }
        // Memorarea primului grup de permisiuni
        if (i % 3 == 2) {
            permision = permision * 10 + oct;
            oct = 0;
        }
    }
    // Completarea field-ului mode
    sprintf(tochar, "%d", permision);
    offset = sizeof((*tar).header.mode) - strlen(tochar) -1;
    memset((*tar).header.mode, '0', offset);
    memcpy((*tar).header.mode + offset, tochar, strlen(tochar));
}

// Functia ce calculeaza timpul crearii in functie de UNIX EPOCH
void calctime(union record *tar, char *c, int *word) {
    char year[5], month[3], day[3], hour[3], minute[3], second[3], tochar[12];
    int i = 0, y, mo, d, h, mi, s, offset;
    time_t epoch;
    // Prelucrarea anului
    while (i < 4) {
        year[i] = c[i];
        i++;
    }
    year[4] = 0;
    i++;
    // Prelucrarea lunii
    while (i < 7) {
        month[i - 5] = c[i];
        i++;
    }
    month[2] = 0;
    i++;
    // Prelucrarea zilei
    while (i < 10) {
        day[i - 8] = c[i];
        i++;
    }
    day[2] = 0;
    c = strtok(NULL, " ");
    (*word)++;
    i = 0;
    // Prelucrarea orei
    while (i < 2) {
        hour[i] = c[i];
        i++;
    }
    hour[2] = 0;
    i++;
    // Prelucrarea minutelor
    while (i < 5) {
        minute[i - 3] = c[i];
        i++;
    }
    minute[2] = 0;
    i++;
    // Prelucrarea secundelor
    while (i < 8) {
        second[i - 6] = c[i];
        i++;
    }
    second[2] = 0;
    c = strtok(NULL, " ");
    (*word)++;
    // Convertirea datelor la int-uri
    y = atoi(year);
    mo = atoi(month);
    d = atoi(day);
    h = atoi(hour);
    mi = atoi(minute);
    s = atoi(second);
    // Calcularea timpului folosind biblioteca time.h
    struct tm time = {s, mi, h, d, mo - 1, (y - 1900)};
    epoch = mktime(&time);
    sprintf(tochar, "%lo", epoch);
    // Adaugarea la campul mtime din header
    offset = sizeof((*tar).header.mtime) - strlen(tochar) -1;
    memset((*tar).header.mtime, '0', offset);
    memcpy((*tar).header.mtime + offset, tochar, strlen(tochar));
}

// Functia principala de create
void create(union record tar, char *archive_name, char *dir_name) {
    // Deschiderea fisierelor necesare
    FILE *archive;
    if ((archive = fopen(archive_name, "wt")) != NULL) {
        FILE *file = fopen("files.txt", "rt");
        FILE *user = fopen("usermap.txt", "rt");
        char *c, line[512], ch = 0, tochar[12], name[100], path[512];
        int i, word, offset, size;
        unsigned int toint;
        FILE *f;
        // Parcurgerea fisierului files.txt linie cu linie si completarea
        // campurilor din header
        while (fgets(line, 512, file) != NULL) {
            // Initializarea elementelor ce nu se modifica
            memset(&tar, 0, 512);
            memcpy(tar.header.magic, "GNUtar ", 7);
            memset(tar.header.chksum, ' ', 8);
            word = 1;
            c = strtok(line, " ");
            while (c != NULL) {
                // Completarea campului mode(permisiuni)
                if (word == 1) {
                    permisions(&tar, c);
                }
                // Completarea campului pentru username
                if (word == 3) {
                    memcpy(tar.header.uname, c, strlen(c));
                }
                // Completarea campului pentru groupname
                if (word == 4) {
                    memcpy(tar.header.gname, c, strlen(c));
                }
                // Completarea campului size
                if (word == 5) {
                    toint = atoi(c);
                    size = toint;
                    sprintf(tochar, "%o", toint);
                    offset = sizeof(tar.header.size) - strlen(tochar) -1;
                    memset(tar.header.size, '0', offset);
                    memcpy(tar.header.size + offset, tochar, strlen(tochar));
                }
                // Completarea campului mtime
                if (word == 6) {
                    calctime(&tar, c, &word);
                }
                // Completarea campurilor name si linkname
                if (word == 9) {
                    c[strlen(c) - 1] = 0;
                    memcpy(tar.header.name, c, strlen(c));
                    memcpy(tar.header.linkname, c, strlen(c));
                    strcpy(name, tar.header.name);
                }
                c = strtok(NULL, " ");
                word++;
            }
            // Completarea campurilor uid si gid din usermap.txt
            fseek(user, 0, SEEK_SET);
            readuser(user, &tar);
            // Completarea campului chksum
            calcchk(&tar);
            // Scrierea header-ului in fisierul arhiva
            for (i = 0; i < 512; i++) {
                fprintf(archive, "%c", tar.charptr[i]);
            }
            // Scrierea in fisierul arhiva a continutului fiecarui fisier ce
            // trebuie arhivat
            memset(path, 0, 512);
            strcpy(path, dir_name);
            strcat(path, name);
            f = fopen(path, "rt");
            readcontent(f, archive, &size);
            fclose(f);
        }
        // Scrierea in fisierul arhiva a 512 octeti de 0 ce semnifica finalul
        for (i = 0; i < 512; i++) {
            fprintf(archive, "%c", ch);
        }
        fclose(file);
        fclose(user);
        fclose(archive);
        printf("> Done!\n");
    } else {
        printf("> Failed!\n");
    }
}
