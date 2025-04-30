#include <stdio.h>
#include <locale.h>
#include "marrakech.h"

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil.1252");

    int numJogadores, turno = 0, dado;

    printf("\n          MARRAKECH          \n\n");
    while (1) {
        printf("Digite a quantidade de jogadores(2 - 4): ");
        scanf("%d", &numJogadores);
        while (getchar() != '\n');

        if (numJogadores >= 2 && numJogadores <= 4) break;

        printf("Por favor, digite uma quantidade de jogadores entre 2 e 4.\n");
    }
       
    Tabuleiro *tabuleiro = criarTabuleiro(TAM);
    Assam *assam = criarAssam(tabuleiro);
    Jogador *jogadores = criarJogadores(numJogadores);
    imprimirTabuleiro(tabuleiro, assam, 0);

    while (1) {
        imprimirMenu(jogadores, turno);
        girarAssam(assam, perguntarGiro(assam));
        imprimirTabuleiro(tabuleiro, assam, 0);
        dado = rolarDado();
        printf("Quantidade de casas a saltar: %d\n", dado);
        avancarAssam(assam, dado);
        imprimirTabuleiro(tabuleiro, assam, 1);
        printf("Onde deseja colocar o tapete: [ 1 / 2 / 3 / 4 / 0 ]\n");
        int posicaoTapete;
        scanf("%d", &posicaoTapete);
        printf("Selecione a direção para colocar o tapete:\n");
        printf("1 -> ↑\n");
        printf("2 -> →\n");
        printf("3 -> ↓\n");
        printf("4 -> ←\n");
        int rotacaoTapete;
        scanf("%d", &rotacaoTapete);
        colocarTapete(assam, posicaoTapete, rotacaoTapete, jogadores, turno);
        imprimirTabuleiro(tabuleiro, assam, 0);
        printf("Pressione ENTER para continuar...");
        scanf("%*c");

        turno = (turno == numJogadores - 1) ? 0 : turno++;
    }
    
    return 0;
}
