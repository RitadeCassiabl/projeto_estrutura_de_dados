#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include "estruturas.h"

#define MAX_LIVROS 10

typedef struct {
    char titulo[MAX_STR];
    char autor[MAX_STR];
    int disponivel;
    Fila fila_reserva; // Cada livro gerencia sua própria fila de espera
} Livro;

typedef struct {
    Livro catalogo[MAX_LIVROS];
    int qtd_livros;
    Pilha caixa_devolucao; // Caixa geral de devoluções da biblioteca
} Biblioteca;

void inicializar_biblioteca(Biblioteca* b);
void adicionar_livro(Biblioteca* b, const char* titulo, const char* autor);
void listar_livros(Biblioteca* b);
void pegar_emprestado(Biblioteca* b, const char* titulo, const char* usuario);
void devolver_na_caixa(Biblioteca* b, const char* titulo);
void processar_caixa_devolucao(Biblioteca* b);

#endif