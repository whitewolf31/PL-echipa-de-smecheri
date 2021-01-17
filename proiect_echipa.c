#include <stdio.h>
#include <stdlib.h>

int numarator(int load, int up, int in) {
    static int num= 0;
    if (up && !load) {
        num++;
        return num;
    }
    if (load) {
        num = in;
        return in;
    }
}

int main(int argc, char *argv[]) {
    FILE *in;
    if (argc > 0) {
        in = fopen(argv[1], "r");
        if (in == NULL) {
            printf("Fisierul nu a putut fi deschis!");
        }
    } else {
        printf("Va rugam sa puneti ca parametru un fisier");
    }
    int *memorie = (int *) malloc(64 * sizeof(int));
    int n, i;
    fscanf(in, "%d", &n);
    for (i = 0; i < n; i++) {
        fscanf(in, "%d", &memorie[i]);
    }
    // Lungime microinstructiune: 9
    int *p = memorie;
    char intrari[8][16] = {"IN/OUT", "LOCURI?", "2ORE?", "NU_A_PLATIT?", "NU_ARE_BANI?", "A_TRECUT?", "TRECUT_OUT"};
    char iesire[8][16] = {"c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8"};
    int end = 0;
    int reset = 0;
    while (!end) {
        reset = 0;
        p = memorie;
        while (!reset) {
            if (!(*p)) {
                reset = 1;
                break;
            } 
            int nevoie_de_input = 0;
            int tip = *p >> 8;
            if (!tip) {
                nevoie_de_input = 1;
            }
            int intrare;
            if (nevoie_de_input) {
                int cod_input = *p >> 5;
                cod_input = cod_input & 7; // 0111
                printf("Introduceti intrarea pentru %s (0 sau 1)\n", intrari[cod_input]);
                scanf("%d", &intrare);
                while (intrare > 2) {
                    printf("Intrare invalida!\n");
                    scanf("%d", &intrare);
                }
            }
            int or_gate = tip | intrare;
            int next_address = numarator(!or_gate, or_gate, *p & 31);
            int copie = *p;
            i = 7;
            while (copie > 1) {
                if ((copie & tip) % 2 == 1) {
                    printf("Iesire: %s\n", iesire[i]);
                }
                copie >>= 1;
                i--;
            }
            p = memorie + next_address;
            printf("%d\n", next_address);
        }
        int cont;
        printf("Vreti sa continuati? (0 sau 1)\n");
        scanf("%d", &cont);
        if (!cont) {
            end = 1;
        }
    }
    free(memorie);
    printf("Program Terminat\n");
    return 0;
}