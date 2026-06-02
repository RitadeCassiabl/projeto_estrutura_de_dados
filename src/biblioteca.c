#include <stdio.h>
#include <string.h>
#include "estruturas.h"

/* Fallback in case MAX_LIVROS isn't defined in estruturas.h */
#ifndef MAX_LIVROS
#define MAX_LIVROS 100
#endif

/* Fallback in case MAX_STR isn't defined in estruturas.h */
#ifndef MAX_STR
#define MAX_STR 256
#endif

typedef struct Biblioteca Biblioteca;
typedef struct Livro Livro;

struct Livro
{
    char titulo[MAX_STR];
    char autor[MAX_STR];
    int disponivel;
    Fila fila_reserva;
};

struct Biblioteca
{
    Livro catalogo[MAX_LIVROS];
    int qtd_livros;
    Pilha caixa_devolucao;
};

void inicializar_biblioteca(Biblioteca *b)
{
    b->qtd_livros = 0;
    inicializar_pilha(&(b->caixa_devolucao));
}

void adicionar_livro(Biblioteca *b, const char *titulo, const char *autor)
{
    if (b->qtd_livros >= MAX_LIVROS)
        return;

    int i = b->qtd_livros;
    strcpy(b->catalogo[i].titulo, titulo);
    strcpy(b->catalogo[i].autor, autor);
    b->catalogo[i].disponivel = 1; // True
    inicializar_fila(&(b->catalogo[i].fila_reserva));

    b->qtd_livros++;
}

void listar_livros(Biblioteca *b)
{
    if (b->qtd_livros == 0)
    {
        printf("Catalogo vazio.\n");
        return;
    }
    printf("\n--- CATALOGO DE LIVROS ---\n");
    for (int i = 0; i < b->qtd_livros; i++)
    {
        printf("'%s' por %s [%s]\n",
               b->catalogo[i].titulo,
               b->catalogo[i].autor,
               b->catalogo[i].disponivel ? "Disponivel" : "Emprestado");
    }
}

int buscar_livro(Biblioteca *b, const char *titulo)
{
    for (int i = 0; i < b->qtd_livros; i++)
    {
        if (strcasecmp(b->catalogo[i].titulo, titulo) == 0)
        {
            return i;
        }
    }
    return -1;
}

void pegar_emprestado(Biblioteca *b, const char *titulo, const char *usuario)
{
    int idx = buscar_livro(b, titulo);
    if (idx == -1)
    {
        printf("Erro: O livro '%s' nao existe no catalogo.\n", titulo);
        return;
    }

    Livro *livro = &(b->catalogo[idx]);

    if (livro->disponivel)
    {
        livro->disponivel = 0;
        printf("Sucesso: '%s' emprestado para %s.\n", livro->titulo, usuario);
    }
    else
    {
        enfileirar(&(livro->fila_reserva), usuario);
        printf("Indisponivel: %s entrou na fila de reserva para '%s' (Posicao: %d).\n",
               usuario, livro->titulo, livro->fila_reserva.tamanho);
    }
}

void devolver_na_caixa(Biblioteca *b, const char *titulo)
{
    int idx = buscar_livro(b, titulo);
    if (idx == -1)
    {
        printf("Erro: O livro '%s' nao pertence a esta biblioteca.\n", titulo);
        return;
    }

    empilhar(&(b->caixa_devolucao), b->catalogo[idx].titulo);
    printf("Livro '%s' depositado na caixa de devolucao rapida.\n", b->catalogo[idx].titulo);
}

void processar_caixa_devolucao(Biblioteca *b)
{
    if (pilha_vazia(&(b->caixa_devolucao)))
    {
        printf("A caixa de devolucao esta vazia. Nada para processar.\n");
        return;
    }

    char titulo_extraido[MAX_STR];
    char proximo_usuario[MAX_STR];

    printf("\n--- Processando Caixa de Devolucao (Pilha - LIFO) ---\n");
    while (desempilhar(&(b->caixa_devolucao), titulo_extraido))
    {
        printf("Processando devolucao de: '%s'\n", titulo_extraido);

        int idx = buscar_livro(b, titulo_extraido);
        Livro *livro = &(b->catalogo[idx]);

        // Se houver alguém na fila de reserva (FIFO) desse livro
        if (desenfileirar(&(livro->fila_reserva), proximo_usuario))
        {
            printf(" -> Livro repassado imediatamente para o proximo da fila: %s!\n", proximo_usuario);
            // Continua como indisponível porque mudou de mãos diretamente
        }
        else
        {
            livro->disponivel = 1;
            printf(" -> Livro devolvido para a estante.\n");
        }
    }
    printf("---------------------------------------------------\n");
}