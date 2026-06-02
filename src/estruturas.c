#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

// --- Implementação da Fila ---
void inicializar_fila(Fila *f)
{
    f->frente = NULL;
    f->tras = NULL;
    f->tamanho = 0;
}

int fila_vazia(Fila *f)
{
    return f->frente == NULL;
}

void enfileirar(Fila *f, const char *usuario)
{
    NoFila *novo = (NoFila *)malloc(sizeof(NoFila));
    strcpy(novo->nome_usuario, usuario);
    novo->proximo = NULL;

    if (fila_vazia(f))
    {
        f->frente = novo;
    }
    else
    {
        f->tras->proximo = novo;
    }
    f->tras = novo;
    f->tamanho++;
}

int desenfileirar(Fila *f, char *destino_nome)
{
    if (fila_vazia(f))
        return 0;

    NoFila *temp = f->frente;
    strcpy(destino_nome, temp->nome_usuario);

    f->frente = f->frente->proximo;
    if (f->frente == NULL)
    {
        f->tras = NULL;
    }

    free(temp);
    f->tamanho--;
    return 1;
}

// --- Implementação da Pilha ---
void inicializar_pilha(Pilha *p)
{
    p->topo = NULL;
}

int pilha_vazia(Pilha *p)
{
    return p->topo == NULL;
}

void empilhar(Pilha *p, const char *titulo)
{
    NoPilha *novo = (NoPilha *)malloc(sizeof(NoPilha));
    strcpy(novo->titulo_livro, titulo);
    novo->proximo = p->topo;
    p->topo = novo;
}

int desempilhar(Pilha *p, char *destino_titulo)
{
    if (pilha_vazia(p))
        return 0;

    NoPilha *temp = p->topo;
    strcpy(destino_titulo, temp->titulo_livro);

    p->topo = p->topo->proximo;
    free(temp);
    return 1;
}