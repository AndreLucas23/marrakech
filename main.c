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
    Jogador *jogador;
    int numJogadores, turno = -1, dado;

    printf("\n           MARRAKECH           \n\n");
    while (1) {
        printf("Digite a quantidade de jogadores ( 2 - 4 ): ");
        scanf("%d", &numJogadores);
        while (getchar() != '\n');

        if (numJogadores >= 2 && numJogadores <= 4)
            break;

        printf("Por favor, digite uma quantidade de jogadores entre 2 e 4.\n");
    }

    Tabuleiro *tabuleiro = criarTabuleiro(TAM);
    Assam *assam = criarAssam(tabuleiro);
    Jogadores *jogadores = criarJogadores(numJogadores);
    imprimirTabuleiro(tabuleiro, assam, 0);

    jogador = jogadorAtual(jogadores, turno);

    while (1) {
        if (fimDeJogo(jogadores)) break;

        turno = (turno == numJogadores - 1) ? 0 : turno + 1;
        jogador = jogadorAtual(jogadores, turno);
        
        while (!jogando(jogador)) {
            turno = (turno == numJogadores - 1) ? 0 : turno + 1;
            jogador = jogadorAtual(jogadores, turno);
        }

        imprimirMenu(jogadores, turno);
        girarAssam(assam, perguntarGiro(assam));
        imprimirTabuleiro(tabuleiro, assam, 0);

        dado = rolarDado();
        printf("Quantidade de casas a saltar: %d\n", dado);

        avancarAssam(tabuleiro, assam, dado);
        imprimirTabuleiro(tabuleiro, assam, 1);

        pagar(tabuleiro, assam, jogadores, turno);

        if (jogando(jogador)) {
            tapeteMetade1 = posicaoTapete(tabuleiro, assam);
            tapeteMetade2 = sentidoTapete(tabuleiro, assam, tapeteMetade1);

            colocarTapete(assam, tapeteMetade1, tapeteMetade2, jogador);

            imprimirTabuleiro(tabuleiro, assam, 0);
        }
    }

    imprimirFim(jogadores, contarPontos(tabuleiro, jogadores));    

    return 0;
}
