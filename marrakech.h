#ifndef MARRAKECH_H
#define MARRAKECH_H
#define TAM 5

typedef struct No No;

typedef struct Tapete Tapete;

typedef struct Assam Assam;

typedef struct Tabuleiro Tabuleiro;

typedef struct Jogador Jogador;

Tabuleiro *criarTabuleiro(int);

Assam *criarAssam(Tabuleiro *);

Jogador *criarJogadores(int);

int imprimirTabuleiro(Tabuleiro *, Assam *);

int imprimirMenu(Jogador *, int);

char perguntarGiro(Assam *assam);

int girarAssam(Assam *, char);

int rolarDado();

int avancarAssam(Assam *, int);

char maiusculo(char);

#endif
