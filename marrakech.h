#ifndef MARRAKECH_H
#define MARRAKECH_H

#define TAM 7

typedef struct No No;

typedef struct Tapetes Tapetes;

typedef struct Tapete Tapete;

typedef struct Assam Assam;

typedef struct Tabuleiro Tabuleiro;

typedef struct Jogador Jogador;

Tabuleiro *criarTabuleiro(int);

Assam *criarAssam(Tabuleiro *);

Jogador **criarJogadores(int);

Tapetes *criarPilha();

int imprimirTabuleiro(Tabuleiro *, Assam *, int);

int imprimirMenu(Jogador **, int);

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

Tapete *topo(Tapetes *);

int altura(Tapetes *);

int jogando(Jogador *);

int pagar(Tabuleiro *, Assam *, Jogador *);

int rolarDado();

char maiusculo(char);

#endif
