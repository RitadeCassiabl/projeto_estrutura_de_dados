#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#define MAX_STR 50

typedef struct NoFila
{
    char nome_usuario[MAX_STR];
    struct NoFila *proximo;
    struct NoFila *anterior;
} NoFila;

typedef struct
{
    NoFila *frente;
    NoFila *tras;
    int tamanho;
} Fila;

void inicializar_fila(Fila *f);
int fila_vazia(Fila *f);
void enfileirar(Fila *f, const char *usuario);
int desenfileirar(Fila *f, char *destino_nome);

typedef struct NoPilha{
    char titulo_livro[MAX_STR];
    struct NoPilha *proximo;
} NoPilha;

typedef struct
{
    NoPilha *topo;
} Pilha;

void inicializar_pilha(Pilha *p);
int pilha_vazia(Pilha *p);
void empilhar(Pilha *p, const char *titulo);
int desempilhar(Pilha *p, char *destino_titulo);

#endif