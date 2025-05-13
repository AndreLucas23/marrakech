#ifndef MARRAKECH_H
#define MARRAKECH_H

#define TAM 7

typedef struct No No;

typedef struct Tapetes Tapetes;

typedef struct Tapete Tapete;

typedef struct Assam Assam;

typedef struct Tabuleiro Tabuleiro;

typedef struct Jogador Jogador;

typedef struct Jogadores Jogadores;

Tabuleiro *criarTabuleiro(int);

Assam *criarAssam(Tabuleiro *);

Jogadores *criarJogadores(int);

Tapetes *criarPilha();

int imprimirTabuleiro(Tabuleiro *, Assam *, int);

int imprimirMenu(Jogadores *, int);

int imprimirFim(Jogadores *, int);

void imprimirColorido(int, char *);

char perguntarGiro(Assam *assam);

int girarAssam(Assam *, char);

int avancarAssam(Tabuleiro *, Assam *, int);

No *posicaoTapete(Tabuleiro *, Assam *);

No *sentidoTapete(Tabuleiro *, Assam *, No *);

int colocarTapete(Assam *, No *, No *, Jogador *);

int calcularArea(Tabuleiro *, No *);

int calcularAreaUtil(Tabuleiro *, No *, int, int ***);

int inserirTapete(Tapetes *, Tapete *);

int contarPontos(Tabuleiro *, Jogadores *);

Tapete *topo(Tapetes *);

int altura(Tapetes *);

Jogador *jogadorAtual(Jogadores *, int);

int jogando(Jogador *);

int pagar(Tabuleiro *, Assam *, Jogadores *, int);

int rolarDado();

int fimDeJogo(Jogadores *);

#endif
