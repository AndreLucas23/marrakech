#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "marrakech.h"

int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil.1252");

    srand(time(NULL));

    No *tapeteMetade1, *tapeteMetade2;
    int numJogadores, turno = 0, dado;

    printf("\n          MARRAKECH          \n\n");
    while (1) {
        printf("Digite a quantidade de jogadores(2 - 4): ");
        scanf("%d", &numJogadores);
        while (getchar() != '\n');

        if (numJogadores >= 2 && numJogadores <= 4)
            break;

        printf("Por favor, digite uma quantidade de jogadores entre 2 e 4.\n");
    }

    Tabuleiro *tabuleiro = criarTabuleiro(TAM);
    Assam *assam = criarAssam(tabuleiro);
    Jogador **jogadores = criarJogadores(numJogadores);
    imprimirTabuleiro(tabuleiro, assam, 0);

    while (1) {
        imprimirMenu(jogadores, turno);
        girarAssam(assam, perguntarGiro(assam));
        imprimirTabuleiro(tabuleiro, assam, 0);
        printf("\n");

        dado = rolarDado();
        printf("Quantidade de casas a saltar: %d\n", dado);

        avancarAssam(tabuleiro, assam, dado);
        imprimirTabuleiro(tabuleiro, assam, 1);
        printf("\n");

        tapeteMetade1 = posicaoTapete(tabuleiro, assam);
        printf("\n");
        tapeteMetade2 = sentidoTapete(tabuleiro, assam, tapeteMetade1);

        colocarTapete(assam, tapeteMetade1, tapeteMetade2, jogadores[turno]);

        imprimirTabuleiro(tabuleiro, assam, 0);
        printf("\nPressione ENTER para continuar...");
        scanf("%*c");

        turno = (turno == numJogadores - 1) ? 0 : turno + 1;
    }

    return 0;
}
