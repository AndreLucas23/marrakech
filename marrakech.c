#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "marrakech.h"

struct No {
    Tapetes *tapetes;
    No *norte;
    No *sul;
    No *oeste;
    No *leste;
    int x;
    int y;
};

struct Tapete {
    int cor;
    Jogador *jogador;
    Tapete *metade;
    Tapete *abaixo;
};

struct Tapetes {
    Tapete *pilhaTapetes;
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
    int indice;
    int tapetes;
    int dinheiro;
    int jogando;
    int pontosFinais;
};

struct Jogadores {
    Jogador **lista;
    int numJogadores;
    int ativos;
};


Tabuleiro *criarTabuleiro(int tam) {
    int i, j, k, l;
    
    Tabuleiro *tabuleiro = (Tabuleiro *)malloc(sizeof(Tabuleiro));
    if (!tabuleiro) {
        free(tabuleiro);
        return NULL;
    }

    No **nos = (No **)malloc(tam * sizeof(No *));
    if (!nos) {
        free(nos);
        return NULL;
    }

    for (i = 0; i < tam; i++) {
        nos[i] = (No *)malloc(tam * sizeof(No));
        if (!nos[i]) {
            for (j = 0; j < i; j++) {
                free(nos[j]);
                return NULL;
            }
        }
    }

    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam; j++) {
            nos[i][j].norte = (i != 0) ? &nos[i - 1][j] :
            (j == 0 || (tam % 2 == 0 && j == tam - 1)) ? &nos[i][j] :
            (j % 2 == 0) ? &nos[i][j - 1] : &nos[i][j + 1];

            nos[i][j].sul = (i != tam - 1) ? &nos[i + 1][j] :
            (j == tam - 1 || (tam % 2 == 0 && j == 0)) ? &nos[i][j] :
            (j % 2 == 0) ? &nos[i][j + 1] : &nos[i][j - 1];

            nos[i][j].oeste = (j != 0) ? &nos[i][j - 1] :
            (i == 0 || (tam % 2 == 0 && i == tam - 1)) ? &nos[i][j] :
            (i % 2 == 0) ? &nos[i - 1][j] : &nos[i + 1][j];

            nos[i][j].leste = (j != tam - 1) ? &nos[i][j + 1] :
            (i == tam - 1 || (tam % 2 == 0 && i == 0)) ? &nos[i][j] :
            (i % 2 == 0) ? &nos[i + 1][j] : &nos[i - 1][j];

            nos[i][j].tapetes = criarPilha();

            nos[i][j].x = i;
            nos[i][j].y = j;
        }
    }

    tabuleiro->inicial = &nos[0][0];
    tabuleiro->central = &nos[tam / 2][tam / 2];
    tabuleiro->tam = tam;

    return tabuleiro;
}

Assam *criarAssam(Tabuleiro *tabuleiro) {
    Assam *assam = (Assam *)malloc(sizeof(Assam));
    if (!assam) {
        free(assam);
        return NULL;
    }

    int sentido = rand() % 4 + 1;

    assam->posicao = tabuleiro->central;

    switch (sentido) {
        case (1):
            assam->sentido = 'N';

            break;
        case (2):
            assam->sentido = 'S';

            break;
        case (3):
            assam->sentido = 'L';

            break;
        case (4):
            assam->sentido = 'O';

            break;
    }

    return assam;
}

Jogadores *criarJogadores(int numJogadores) {
    int i, j;

    Jogadores *jogadores = (Jogadores *)malloc(sizeof(Jogadores));
    if (!jogadores) {
        free(jogadores);
        return NULL;
    }

    jogadores->lista = (Jogador **)malloc(numJogadores * sizeof(Jogador *));
    if (!jogadores->lista) {
        free(jogadores->lista);
        free(jogadores);
        return NULL;
    }

    jogadores->numJogadores = numJogadores;

    for (i = 0; i < numJogadores; i++) {
        jogadores->lista[i] = (Jogador *)malloc(sizeof(Jogador));
        if (!jogadores->lista[i]) {
            for (j = 0; j < numJogadores; j++) free(jogadores->lista[j]);
            return NULL;
        }

        jogadores->ativos = numJogadores;

        jogadores->lista[i]->tapetes = (numJogadores == 2 || numJogadores == 4) ? 48 / numJogadores : 15;
        jogadores->lista[i]->dinheiro = 30;
        jogadores->lista[i]->indice = i;
        jogadores->lista[i]->jogando = 1;
    }

    return jogadores;
}

Tapetes *criarPilha() {
    Tapetes *pilha = (Tapetes *)malloc(sizeof(Tapetes));
    if (!pilha) {
        free(pilha);
        return NULL;
    }

    pilha->pilhaTapetes = NULL;
    pilha->altura = 0;

    return pilha;
}

int imprimirTabuleiro(Tabuleiro *tabuleiro, Assam *assam, int acao) {
    if (!tabuleiro || !assam) return 0;

    int i, j, valido1, valido2, valido3, valido4;
    No *q;

    printf("\n +");
    for (i = 0; i < tabuleiro->tam; i++) printf("-+");
    printf("\n");

    for (i = 0; i < tabuleiro->tam; i++) {
        q = tabuleiro->inicial;

        for (j = 0; j < i; j++) q = q->sul;

        printf(" |");
        
        for (j = 0; j < tabuleiro->tam; j++) {
            if (acao == 0) {
                if (q == assam->posicao) {
                    switch (assam->sentido) {
                        case ('N'):
                            if (altura(assam->posicao->tapetes)) imprimirColorido(topo(assam->posicao->tapetes)->cor, "^");
                            else printf("^");

                            break;
                        case ('S'):
                            if (altura(assam->posicao->tapetes)) imprimirColorido(topo(assam->posicao->tapetes)->cor, "v");
                            else printf("v");

                            break;
                        case ('L'):
                            if (altura(assam->posicao->tapetes)) imprimirColorido(topo(assam->posicao->tapetes)->cor, ">");
                            else printf(">");

                            break;
                        case ('O'):
                            if (altura(assam->posicao->tapetes)) imprimirColorido(topo(assam->posicao->tapetes)->cor, "<");
                            else printf("<");

                            break;
                    }
                } else if (!altura(q->tapetes)) printf(" ");
                else if (altura(q->tapetes)) imprimirColorido(topo(q->tapetes)->cor, "T");
            } else if (acao == 1) {   
                if (assam->posicao->x == 0) valido1 = 0;

                if (assam->posicao->y == tabuleiro->tam - 1) valido2 = 0;

                if (assam->posicao->x == tabuleiro->tam - 1) valido3 = 0;

                if (assam->posicao->y == 0) valido4 = 0;

                if (q == assam->posicao) {
                    switch (assam->sentido) {
                        case ('N'):
                            if (altura(assam->posicao->tapetes)) imprimirColorido(topo(assam->posicao->tapetes)->cor, "^");
                            else printf("^");

                            break;
                        case ('S'):
                            if (altura(assam->posicao->tapetes)) imprimirColorido(topo(assam->posicao->tapetes)->cor, "v");
                            else printf("v");

                            break;
                        case ('L'):
                            if (altura(assam->posicao->tapetes)) imprimirColorido(topo(assam->posicao->tapetes)->cor, ">");
                            else printf(">");

                            break;
                        case ('O'):
                            if (altura(assam->posicao->tapetes)) imprimirColorido(topo(assam->posicao->tapetes)->cor, "<");
                            else printf("<");

                            break;
                    }
                } else if (q == assam->posicao->norte && valido1) (altura(q->tapetes)) ? imprimirColorido(topo(q->tapetes)->cor, "1") : printf("1");
                else if (q == assam->posicao->leste && valido2) (altura(q->tapetes)) ? imprimirColorido(topo(q->tapetes)->cor, "2") : printf("2");
                else if (q == assam->posicao->sul && valido3) (altura(q->tapetes)) ? imprimirColorido(topo(q->tapetes)->cor, "3") : printf("3");
                else if (q == assam->posicao->oeste && valido4) (altura(q->tapetes)) ? imprimirColorido(topo(q->tapetes)->cor, "4") : printf("4");
                else (altura(q->tapetes)) ? imprimirColorido(topo(q->tapetes)->cor, "T") : printf(" ");
            }

            printf("|");
            
            q = q->leste;
        }

        printf("\n");
    }

    printf(" +");
    for (i = 0; i < tabuleiro->tam; i++) printf("-+");
    printf("\n\n");

    return 1;
}

int imprimirMenu(Jogadores *jogadores, int turno) {
    if (!jogadores)return 0;

    printf("------------------\n");
    printf("JOGADOR %d\n", turno + 1);
    printf("Tapetes: %d\n", jogadores->lista[turno]->tapetes);
    printf("Moedas: %d\n", jogadores->lista[turno]->dinheiro);
    printf("\n");

    return 1;
}

int imprimirFim(Jogadores *jogadores, int numVencedor) {
    int i;

    printf("\n   FIM DE JOGO\n\n");
    printf("+-----------------+\n");
    printf("|  RANKING FINAL  |\n");
    printf("+-----------------+\n");
    for (i = 0; i < jogadores->numJogadores; i++) {
        printf("|    JOGADOR %d    |\n", i + 1);

        if (jogadores->lista[i]->pontosFinais < 10) 
            printf("|  PONTUACAO: %d   |\n", jogadores->lista[i]->pontosFinais);
        else printf("|  PONTUACAO: %d  |\n", jogadores->lista[i]->pontosFinais);

        if (jogadores->lista[i]->dinheiro < 10)
            printf("|   MOEDA(S): %d   |\n", jogadores->lista[i]->dinheiro);
        else printf("|   MOEDA(S): %d  |\n", jogadores->lista[i]->dinheiro);


        printf("+-----------------+\n");
    }

    if (numVencedor == -1) printf("O jogo terminou empatado!\n\n");
    else printf("\nO jogador %d venceu!\n\n", numVencedor + 1);

    return 1;
}

void imprimirColorido(int cor, char *msg) {
    switch (cor) {
        case 0: printf("\x1b[34m%s\x1b[0m", msg); break;
        case 1: printf("\x1b[31m%s\x1b[0m", msg); break;
        case 2: printf("\x1b[32m%s\x1b[0m", msg); break;
        case 3: printf("\x1b[33m%s\x1b[0m", msg); break;
        default: printf("T"); break;
    }
}

char perguntarGiro(Assam *assam) {
    if (!assam) return '0';

    char sentido;
    int valido = 0;

    while (1) {
        switch (assam->sentido) {
            case ('N'):
                printf("Para que sentido Assam deve olhar [ N / L / O ]? ");
                scanf("%c", &sentido);
                sentido = toupper(sentido);

                if (sentido == 'N' || sentido == 'L' || sentido == 'O') {
                    valido = 1;
                    break;
                }

                printf("Por favor, digite um dos sentidos entre N, L, O.\n");
                break;
            case ('S'):
                printf("Para que sentido Assam deve olhar [ S / L / O ]? ");
                scanf("%c", &sentido);
                sentido = toupper(sentido);

                if (sentido == 'S' || sentido == 'L' || sentido == 'O') {
                    valido = 1;
                    break;
                }

                printf("Por favor, digite um dos sentidos entre S, L, O.\n");
                break;
            case ('L'):
                printf("Para que sentido Assam deve olhar [ N / S / L ]? ");
                scanf("%c", &sentido);
                sentido = toupper(sentido);

                if (sentido == 'N' || sentido == 'S' || sentido == 'L') {
                    valido = 1;
                    break;
                }

                printf("Por favor, digite um dos sentidos entre N, S, L.\n");
                break;
            case ('O'):
                printf("Para que sentido Assam deve olhar [ N / S / O ]? ");
                scanf("%c", &sentido);
                sentido = toupper(sentido);

                if (sentido == 'N' || sentido == 'S' || sentido == 'O') {
                    valido = 1;
                    break;
                }

                printf("Por favor, digite um dos sentidos entre N, S, O.\n");
                break;
        }

        if (valido == 1) break;
    }

    while (getchar() != '\n');

    printf("------------------\n");

    return sentido;
}

int girarAssam(Assam *assam, char sentido) {
    if (!assam) return 0;

    assam->sentido = sentido;

    return 1;
}

int avancarAssam(Tabuleiro *tabuleiro, Assam *assam, int casas) {
    if (!assam) return 0;

    No *posAnterior;
    int i;

    for (i = 0; i < casas; i++) {
        switch (assam->sentido) {
            case ('N'):
                posAnterior = assam->posicao;

                assam->posicao = assam->posicao->norte;

                if (posAnterior == assam->posicao &&
                posAnterior->x == 0 &&
                posAnterior->y == 0) assam->sentido = 'L';
                else if (tabuleiro->tam % 2 == 0 &&
                posAnterior == assam->posicao &&
                posAnterior->x == 0 &&
                posAnterior->y == tabuleiro->tam - 1) assam->sentido = 'O';
                else if (posAnterior->x == 0) assam->sentido = 'S';

                break;
            case ('S'):
                posAnterior = assam->posicao;

                assam->posicao = assam->posicao->sul;

                if (posAnterior == assam->posicao &&
                posAnterior->x == tabuleiro->tam - 1 &&
                posAnterior->y == tabuleiro->tam - 1) assam->sentido = 'O';
                else if (tabuleiro->tam % 2 == 0 &&
                posAnterior == assam->posicao &&
                posAnterior->x == tabuleiro->tam - 1 &&
                posAnterior->y == 0) assam->sentido = 'L';
                else if (posAnterior->x == tabuleiro->tam - 1) assam->sentido = 'N';
                
                
                break;
            case ('L'):
                posAnterior = assam->posicao;

                assam->posicao = assam->posicao->leste;

                if (posAnterior == assam->posicao &&
                posAnterior->x == tabuleiro->tam - 1 &&
                posAnterior->y == tabuleiro->tam - 1) assam->sentido = 'N';
                else if (tabuleiro->tam % 2 == 0 &&
                posAnterior == assam->posicao &&
                posAnterior->x == 0 &&
                posAnterior->y == tabuleiro->tam - 1) assam->sentido = 'S';
                else if (posAnterior->y == tabuleiro->tam - 1) assam->sentido = 'O';

                break;
            case ('O'):
                posAnterior = assam->posicao;
                
                assam->posicao = assam->posicao->oeste;

                if (posAnterior == assam->posicao &&
                posAnterior->x == 0 &&
                posAnterior->y == 0) assam->sentido = 'S';
                else if (tabuleiro->tam % 2 == 0 &&
                posAnterior == assam->posicao &&
                posAnterior->x == tabuleiro->tam - 1 &&
                posAnterior->y == 0) assam->sentido = 'N';
                else if (posAnterior->y == 0) assam->sentido = 'L';

                break;
        }
    }

    return 1;
}

No *posicaoTapete(Tabuleiro *tabuleiro, Assam *assam) {
    if (!tabuleiro || !assam) return NULL;

    No *tapetePonto;
    int posicaoTapete, valido1 = 1, valido2 = 1, valido3 = 1, valido4 = 1;

    if (assam->posicao->x == 0) valido1 = 0;

    if (assam->posicao->y == tabuleiro->tam - 1) valido2 = 0;

    if (assam->posicao->x == tabuleiro->tam - 1) valido3 = 0;

    if (assam->posicao->y == 0) valido4 = 0;

    while (1) {
        printf("Onde deseja colocar o tapete [");
        if (valido1) printf(" 1 /");
        if (valido2) printf(" 2 /");
        if (valido3) printf(" 3 /");
        if (valido4) printf(" 4 ");
        printf("]? ");

        scanf("%d", &posicaoTapete);
        while (getchar() != '\n');
        printf("\n");

        if (posicaoTapete == 0 || posicaoTapete == 1 && valido1 || posicaoTapete == 2 && valido2 ||
        posicaoTapete == 3 && valido3 || posicaoTapete == 4 && valido4) break;

        printf("Por favor, digite uma das posicoes entre");
        if (valido1) printf(" 1,");
        if (valido2) printf(" 2,");
        if (valido3) printf(" 3,");
        if (valido4) printf(" 4");
        printf("\n\n");
    }

    if (posicaoTapete == 1) tapetePonto = assam->posicao->norte;
    else if (posicaoTapete == 2) tapetePonto = assam->posicao->leste;
    else if (posicaoTapete == 3) tapetePonto = assam->posicao->sul;
    else if (posicaoTapete == 4) tapetePonto = assam->posicao->oeste;

    return tapetePonto;
    
}

No *sentidoTapete(Tabuleiro *tabuleiro, Assam *assam, No *posicaoTapete) {
    if (!tabuleiro || !assam) return NULL;

    No *tapeteMetade;
    int sentidoTapete, valido1, valido2, valido3, valido4;

    if (posicaoTapete->x == 0 ||
    posicaoTapete->norte == assam->posicao) valido1 = 0;

    if (posicaoTapete->y == tabuleiro->tam - 1 ||
    posicaoTapete->leste == assam->posicao) valido2 = 0;

    if (posicaoTapete->x == tabuleiro->tam - 1 ||
    posicaoTapete->sul == assam->posicao) valido3 = 0;

    if (posicaoTapete->y == 0 ||
    posicaoTapete->oeste == assam->posicao) valido4 = 0;

    while (1) {
        if (valido1) printf("1) ^\n");
        if (valido2) printf("2) >\n");
        if (valido3) printf("3) v\n");
        if (valido4) printf("4) <\n");

        printf("Digite o sentido do tapete: ");
        scanf("%d", &sentidoTapete);
        while (getchar() != '\n');

        if ((sentidoTapete == 1 &&
        topo(posicaoTapete->tapetes) &&
        topo(posicaoTapete->norte->tapetes) &&
        topo(posicaoTapete->tapetes)->metade == topo(posicaoTapete->norte->tapetes)) ||
        (sentidoTapete == 2 &&
        topo(posicaoTapete->tapetes) &&
        topo(posicaoTapete->leste->tapetes) &&
        topo(posicaoTapete->tapetes)->metade == topo(posicaoTapete->leste->tapetes)) ||
        (sentidoTapete == 3 &&
        topo(posicaoTapete->tapetes) &&
        topo(posicaoTapete->sul->tapetes) &&
        topo(posicaoTapete->tapetes)->metade == topo(posicaoTapete->sul->tapetes)) ||
        (sentidoTapete == 4 &&
        topo(posicaoTapete->tapetes) &&
        topo(posicaoTapete->oeste->tapetes) &&
        topo(posicaoTapete->tapetes)->metade == topo(posicaoTapete->oeste->tapetes))) {
            printf("\nUm tapete nao pode ser sobreposto por outro\n");
            continue;
        }

        if (sentidoTapete == 1 && valido1 || sentidoTapete == 2 && valido2 ||
        sentidoTapete == 3 && valido3 || sentidoTapete == 4 && valido4) break;

        printf("\nPor favor, digite um sentido valido\n");
    }

    if (sentidoTapete == 1) tapeteMetade = posicaoTapete->norte;
    else if (sentidoTapete == 2) tapeteMetade = posicaoTapete->leste;
    else if (sentidoTapete == 3) tapeteMetade = posicaoTapete->sul;
    else if (sentidoTapete == 4) tapeteMetade = posicaoTapete->oeste;

    return tapeteMetade;
}

int colocarTapete(Assam *assam, No *posicaoTapete, No *tapeteMetade, Jogador *jogador) {
    if (!assam) return 0;

    Tapete *metade1 = (Tapete *)malloc(sizeof(Tapete));
    if (!metade1) return 0;

    metade1->jogador = jogador;
    metade1->cor = jogador->indice;
    metade1->abaixo = NULL;

    Tapete *metade2 = (Tapete *)malloc(sizeof(Tapete));
    if (!metade2) return 0;

    metade2->jogador = jogador;
    metade2->cor = jogador->indice;
    metade2->abaixo = NULL;

    metade1->metade = metade2;
    metade2->metade = metade1;

    inserirTapete(posicaoTapete->tapetes, metade1);
    inserirTapete(tapeteMetade->tapetes, metade2);

    jogador->tapetes--;

    if (jogador->tapetes <= 0) jogador->jogando = 0;

    return 1;
}

int calcularArea(Tabuleiro *tabuleiro, No *posicao) {
    int i, j, **visitados = (int **)malloc(tabuleiro->tam * sizeof(int *));
    if (!visitados) return 0;

    if (!altura(posicao->tapetes)) return 0;

    int areaNorte, areaSul, areaLeste, areaOeste;

    for (i = 0; i < tabuleiro->tam; i++) {
        visitados[i] = (int *)malloc(tabuleiro->tam * sizeof(int));
        if (!visitados[i]) {
            for (j = 0; j < tabuleiro->tam; j++) free(visitados[j]);
            return 0;
        }
    }

    for (i = 0; i < tabuleiro->tam; i++) {
        for (j = 0; j < tabuleiro->tam; j++) {
            visitados[i][j] = 0;
        }
    }

    visitados[posicao->x][posicao->y] = 1;

    areaNorte = (posicao->x != 0) ?
    calcularAreaUtil(tabuleiro, posicao->norte, topo(posicao->tapetes)->cor, &visitados) : 0;
    areaSul = (posicao->x != tabuleiro->tam - 1) ?
    calcularAreaUtil(tabuleiro, posicao->sul, topo(posicao->tapetes)->cor, &visitados) : 0;
    areaLeste = (posicao->y != tabuleiro->tam - 1) ?
    calcularAreaUtil(tabuleiro, posicao->leste, topo(posicao->tapetes)->cor, &visitados) : 0;
    areaOeste = (posicao->y != 0) ?
    calcularAreaUtil(tabuleiro, posicao->oeste, topo(posicao->tapetes)->cor, &visitados) : 0;

    return 1 + areaNorte + areaSul + areaLeste + areaOeste;
}

int calcularAreaUtil(Tabuleiro *tabuleiro, No *posicao, int cor, int ***visitados) {
    int areaNorte, areaSul, areaLeste, areaOeste;

    if ((*visitados)[posicao->x][posicao->y] ||
    !altura(posicao->tapetes) ||
    topo(posicao->tapetes)->cor != cor) return 0;

    (*visitados)[posicao->x][posicao->y] = 1;

    areaNorte = (posicao->x != 0) ?
    calcularAreaUtil(tabuleiro, posicao->norte, cor, visitados) : 0;
    areaSul = (posicao->x != tabuleiro->tam - 1) ?
    calcularAreaUtil(tabuleiro, posicao->sul, cor, visitados) : 0;
    areaLeste = (posicao->y != tabuleiro->tam - 1) ?
    calcularAreaUtil(tabuleiro, posicao->leste, cor, visitados) : 0;
    areaOeste = (posicao->y != 0 ) ?
    calcularAreaUtil(tabuleiro, posicao->oeste, cor, visitados) : 0;

    return 1 + areaNorte + areaSul + areaLeste + areaOeste;
}

int pagar(Tabuleiro *tabuleiro, Assam *assam, Jogadores *jogadores, int turno) {
    if (!tabuleiro || !assam || !jogadores) return 0;

    Jogador *jogador1 = jogadores->lista[turno];

    if (!altura(assam->posicao->tapetes) ||
    topo(assam->posicao->tapetes)->jogador == jogador1 ||
    !topo(assam->posicao->tapetes)->jogador->jogando) return 0;

    Jogador *jogador2 = topo(assam->posicao->tapetes)->jogador;

    int valor = calcularArea(tabuleiro, assam->posicao);

    if (jogador1->dinheiro >= valor) {
        jogador1->dinheiro -= valor;
        
        jogador2->dinheiro += valor;

        printf("O jogador %d pagou %d moedas ao jogador %d!\n\n", jogador1->indice + 1, valor, jogador2->indice + 1);
    } else if (jogador1->dinheiro == 0) {
        printf("O jogador %d foi eliminado!\n\n", jogador1->indice + 1);
    } else {
        jogador2->dinheiro += jogador1->dinheiro;

        printf("O jogador %d pagou %d moeda(s) ao jogador %d e esta fora do jogo!\n\n",
        jogador1->indice + 1, jogador1->dinheiro, jogador2->indice + 1);

        jogador1->dinheiro = 0;
        jogador1->tapetes = 0;
        jogador1->jogando = 0;

        jogadores->ativos--;
    }

    return 1;
}

int inserirTapete(Tapetes *pilha, Tapete *tapete) {
    if (!pilha) return 0;

    tapete->abaixo = pilha->pilhaTapetes;
    pilha->pilhaTapetes = tapete;

    pilha->altura++;

    return 1;
}

int contarPontos(Tabuleiro *tabuleiro, Jogadores *jogadores) {
    if (!tabuleiro || !jogadores) return 0;

    No *q;
    int i, j, maiorPontuacao, numVencedor, empate = 0;

    for (i = 0; i < jogadores->numJogadores; i++) 
        jogadores->lista[i]->pontosFinais = jogadores->lista[i]->dinheiro;

    for (i = 0; i < tabuleiro->tam; i++) {
        q = tabuleiro->inicial;

        for (j = 0; j < i; j++) q = q->sul;

        for (j = 0; j < tabuleiro->tam; j++) {
            if (q->tapetes && topo(q->tapetes) && topo(q->tapetes)->jogador) 
                topo(q->tapetes)->jogador->pontosFinais++;

            q = q->leste;
        }
    }

    numVencedor = 0;
    maiorPontuacao = jogadores->lista[0]->pontosFinais;

    for (i = 1; i < jogadores->numJogadores; i++) {
        if (jogadores->lista[i]->pontosFinais > maiorPontuacao) {
            maiorPontuacao = jogadores->lista[i]->pontosFinais;
            numVencedor = jogadores->lista[i]->indice;
        }
    }

    for (i = 0; i < jogadores->numJogadores; i++) {
        if (numVencedor != jogadores->lista[i]->indice &&
        maiorPontuacao == jogadores->lista[i]->pontosFinais) empate = 1;
    }

    if (empate) {
        maiorPontuacao = jogadores->lista[0]->dinheiro;

        for (i = 1; i < jogadores->numJogadores; i++) {
            if (jogadores->lista[i]->dinheiro > maiorPontuacao) {
                maiorPontuacao = jogadores->lista[i]->dinheiro;
                numVencedor = jogadores->lista[i]->indice;
                empate = 0;
            }
        }

        for (i = 1; i < jogadores->numJogadores; i++) {
            if (jogadores->lista[i]->pontosFinais == maiorPontuacao) empate = 1;
        }
    }

    if (empate) return -1;

    return numVencedor;
}

Tapete *topo(Tapetes *pilha) {
    if (!pilha) return NULL;

    return pilha->pilhaTapetes;
}

int altura(Tapetes *pilha) {
    if (!pilha) return 0;

    return pilha->altura;
}

Jogador *jogadorAtual(Jogadores *jogadores, int turno) {
    return jogadores->lista[turno];
}

int jogando(Jogador *jogador) {
    if (!jogador) return 0;

    if (jogador->jogando) return 1;
    else return 0;
}

int rolarDado() {
    printf("Aperte ENTER para rolar o dado...");
    scanf("%*c");

    return rand() % 3 + 1;
}

int fimDeJogo(Jogadores *jogadores) {
    int i, fimTapetes = 1, fimAtivos = 1;

    for (i = 0; i < jogadores->numJogadores; i++) 
        if (jogadores->lista[i]->tapetes > 0) fimTapetes = 0;

    if (jogadores->ativos > 1) fimAtivos = 0;

    if (fimTapetes || fimAtivos) return 1;
    
    return 0;
}
