#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/livro.h"

struct livro{
    char titulo[100];
    char genero[100];
    char editora[100];
    char autor[100];
    int ano;
    struct livro* ant; 
    struct livro* prox;
};

Livro* criarListaLivros() {
    return NULL;
}

Livro* criarLivro(Livro* inicio, char* titulo, char* genero, char* editora, char* autor, int ano) {
    Livro* novo = (Livro*)malloc(sizeof(Livro));
    if (novo == NULL) {
        printf("Dados insuficientes");
        exit(1);
    }
    
    strcpy(novo->titulo, titulo);
    strcpy(novo->genero, genero);
    strcpy(novo->editora, editora);
    strcpy(novo->autor, autor);
    novo->ano = ano;
    novo->prox = inicio;
    novo->ant = NULL;

    if (inicio != NULL) {
        inicio->ant = novo;
    }

    return novo;
}

void imprimirLivros(Livro* l) {
    Livro* atual = l;
    
    if (atual == NULL) {
        printf("Nenhum livro encontrado\n");
        return;
    }

    printf("\n=== Livros Cadastrados ===\n");
    while (atual != NULL) {
        printf("Título: %s\nGênero: %s\nAutor: %s\nEditora: %s\nAno: %i", atual->titulo, atual->genero, atual->autor, atual->editora, atual->ano);
        atual = atual->prox;
    }
    printf("=======================\n");
}


Livro* excluirLivro(Livro* lista, char* titulo) {
    if (lista == NULL) {
        printf("A lista está vazia\n");
        return NULL;
    }

    Livro* atual = lista;

    while (atual != NULL && strcmp(atual->titulo, titulo) != 0) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Livro '%s' nao encontrado\n", titulo);
        return lista;
    }

    if (atual == lista) {
        lista = atual->prox;
    }

    if (atual->prox != NULL) {
        atual->prox->ant = atual->ant;
    }

    if (atual->ant != NULL) {
        atual->ant->prox = atual->prox;
    }

    free(atual);
    printf("Livro '%s' deletado com sucesso\n", titulo);

    return lista;
}