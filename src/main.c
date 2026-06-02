#include <stdio.h>
#include <string.h>
#include "biblioteca.h"

void limpar_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void ler_string(char *destino, int tamanho)
{
    fgets(destino, tamanho, stdin);
    destino[strcspn(destino, "\n")] = '\0'; // Remove o '\n' do final
}

int main()
{
    Biblioteca bib;
    inicializar_biblioteca(&bib);

    // Inicializando livros no catálogo
    adicionar_livro(&bib, "O Hobbit", "J.R.R. Tolkien");
    adicionar_livro(&bib, "Duna", "Frank Herbert");
    adicionar_livro(&bib, "Cujo", "Stephen King");

    int opcao;
    char titulo[MAX_STR];
    char usuario[MAX_STR];

    do
    {
        printf("\n=== SISTEMA DE BIBLIOTECA ===\n");
        printf("1. Listar Catalogo\n");
        printf("2. Pegar Livro Emprestado / Reservar\n");
        printf("3. Devolver Livro (Jogar na Caixa)\n");
        printf("4. Processar Caixa de Devolucoes (Pilha)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1)
        {
            opcao = -1;
            limpar_buffer();
        }
        else
        {
            limpar_buffer();
        }

        switch (opcao)
        {
        case 1:
            listar_livros(&bib);
            break;
        case 2:
            printf("Nome do usuario: ");
            ler_string(usuario, MAX_STR);
            printf("Titulo do livro: ");
            ler_string(titulo, MAX_STR);
            pegar_emprestado(&bib, titulo, usuario);
            break;
        case 3:
            printf("Titulo do livro que esta devolvendo: ");
            ler_string(titulo, MAX_STR);
            devolver_na_caixa(&bib, titulo);
            break;
        case 4:
            processar_caixa_devolucao(&bib);
            break;
        case 0:
            printf("Encerrando o sistema da biblioteca. Ate logo!\n");
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}