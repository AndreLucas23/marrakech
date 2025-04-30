#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "marrakech.h"

struct No {
    Tapete *tapetes;
    No *norte;
    No *sul;
    No *oeste;
    No *leste;
};

struct Tapete {
    char *cores;
    int altura;
};

struct Assam {
    char sentido;
    No *posicao;
};

struct Tabuleiro {
    No *inicial;
    No *central;
    int tam;
};

struct Jogador {
    int tapetes;
    int dinheiro;
};

Tabuleiro *criarTabuleiro(int tam) {
    int i, j, k, l;
    Tabuleiro *tabuleiro = (Tabuleiro *)malloc(sizeof(Tabuleiro));
    if (tabuleiro == NULL) {
        free(tabuleiro);
        return NULL;
    }

    No **nos = (No **)malloc(tam * sizeof(No *));
    if (nos == NULL) {
        free(nos);
        return NULL;        
    }

    for (i = 0; i < tam; i++) {
        nos[i] = (No *)malloc(tam * sizeof(No));
        if (nos[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(nos[j]);
                return NULL;
            }
        }
    }

    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam; j++) {
            nos[i][j].norte = (i == 0) ? &nos[tam - 1][j] : &nos[i - 1][j];
            nos[i][j].sul = (i == tam - 1) ? &nos[0][j] : &nos[i + 1][j];
            nos[i][j].oeste = (j == 0) ? &nos[i][tam - 1] : &nos[i][j - 1];
            nos[i][j].leste = (j == tam - 1) ? &nos[i][0] : &nos[i][j + 1];

            nos[i][j].tapetes = (Tapete *)malloc(sizeof(Tapete));
            if (nos[i][j].tapetes == NULL) {
                for (k = 0; k < i; k++) {
                    for (l = 0; l < tam; l++) {
                        if (k >= i && l > j) break;
                        free(&nos[k][l]);
                    }
                }
            }

            nos[i][j].tapetes->cores = (char *)malloc(48 * sizeof(char));
            nos[i][j].tapetes->altura = 0;
        }
    }

    tabuleiro->inicial = &nos[0][0];
    tabuleiro->central = &nos[tam / 2][tam / 2];
    tabuleiro->tam = tam;

    return tabuleiro;
}

Assam *criarAssam(Tabuleiro *tabuleiro) {
    Assam *assam = (Assam *)malloc(sizeof(Assam));
    if (assam == NULL) {
        free(assam);
        return NULL;
    }

    assam->posicao = tabuleiro->central;
    assam->sentido = 'N';

    return assam;
}

Jogador *criarJogadores(int numJogadores) {
    int i;

    Jogador *jogadores = (Jogador *)malloc(numJogadores * sizeof(Jogador));
    if (jogadores == NULL) {
        free(jogadores);
        return NULL;
    }

    for (i = 0; i < numJogadores; i++) {
        jogadores[i].tapetes = (numJogadores == 2 || numJogadores == 4) ? 48 / numJogadores : 15;
        jogadores[i].dinheiro = 30;
    }

    return jogadores;
}

int imprimirTabuleiro(Tabuleiro *tabuleiro, Assam *assam) {
    if (tabuleiro == NULL || assam == NULL) return 0;

    int i, j;
    No *q;

    printf("\n +");
    for (i = 0; i < tabuleiro->tam; i++) printf("-+");
    printf("\n");

    for (i = 0; i < tabuleiro->tam; i++) {
        q = tabuleiro->inicial;
        for (j = 0; j < i; j++) q = q->sul;
        printf(" |");
        for (j = 0; j < tabuleiro->tam; j++) {
            if (q == assam->posicao) {
                switch (assam->sentido) {
                    case ('N'):
                        printf("^|");
                        break;
                    case ('S'):
                        printf("v|");
                        break;
                    case ('L'):
                        printf(">|");
                        break;
                    case ('O'):
                        printf("<|");
                        break;
                }
            } else if (q->tapetes->altura == 0) printf(" |");
            else if (q->tapetes->cores[q->tapetes->altura] == 'A') printf("A|");
            q = q->leste;
        }
        printf("\n");
    }

    printf(" +");
    for (i = 0; i < tabuleiro->tam; i++) printf("-+");
    printf("\n");

    return 1;
}

int imprimirMenu(Jogador *jogadores, int turno) {
    if (jogadores == NULL) return 0;

    printf("\n------------------\n");
    printf("Jogador %d:\n", turno + 1);
    printf("Tapetes: %d\n", jogadores[turno].tapetes);
    printf("Moedas: %d\n", jogadores[turno].dinheiro);
    printf("\n");

    return 1;
}

char perguntarGiro(Assam *assam) {
    char sentido;
    int valido = 0;
    
    while (1) {
        switch(assam->sentido) {
            case ('N'):
                printf("Para que sentido Assam deve olhar (N/L/O)? ");
                scanf("%c", &sentido);
                sentido = maiusculo(sentido);
                if (sentido == 'N' || sentido == 'L' || sentido == 'O') {
                    valido = 1;
                    break;
                }
                printf("Por favor, digite um dos sentidos entre N, L e O.\n");
                break;
            case ('S'):
                printf("Para que sentido Assam deve olhar (S/L/O)? ");
                scanf("%c", &sentido);
                sentido = maiusculo(sentido);
                if (sentido == 'S' || sentido == 'L' || sentido == 'O') {
                    valido = 1;
                    break;
                }
                printf("Por favor, digite um dos sentidos entre S, L e O.\n");
                break;
            case ('L'):
                printf("Para que sentido Assam deve olhar (N/S/L)? ");
                scanf("%c", &sentido);
                sentido = maiusculo(sentido);
                if (sentido == 'N' || sentido == 'S' || sentido == 'L') {
                    valido = 1;
                    break;
                }
                printf("Por favor, digite um dos sentidos entre N, S e L.\n");
                break;
            case ('O'):
                printf("Para que sentido Assam deve olhar (N/S/O)? ");
                scanf("%c", &sentido);
                sentido = maiusculo(sentido);
                if (sentido == 'N' || sentido == 'S'|| sentido == 'O') {
                    valido = 1;
                    break;
                }
                printf("Por favor, digite um dos sentidos entre N, S e O.\n");    
                break;
        }

        if (valido == 1) break;
    }

    while(getchar() != '\n');
    printf("------------------\n");
    return sentido;
}

int girarAssam(Assam *assam, char sentido) {
    if (assam == NULL) return 0;

    assam->sentido = sentido;

    return 1;
}

int rolarDado() {
    printf("Aperte ENTER para rolar o dado...");
    scanf("%*c");

    return rand() % 3 + 1;
}

int avancarAssam(Assam *assam, int casas) {
    if (assam == NULL) return 0;

    int i;

    for (i = 0; i < casas; i++) {
        switch (assam->sentido) {
            case ('N'):
                assam->posicao = assam->posicao->norte;
                break;
            case ('S'):
                assam->posicao = assam->posicao->sul;
                break;
            case ('L'):
                assam->posicao = assam->posicao->leste;
                break;
            case ('O'):
                assam->posicao = assam->posicao->oeste;
                break;
        }
    }
    return 1;
}

char maiusculo(char letra) {
    return toupper((unsigned char)letra);
}