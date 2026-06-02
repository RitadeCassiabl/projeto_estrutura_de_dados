#include <stdio.h>
#include <string.h>
// Puxando da pasta header:
#include "header/biblioteca.h"

// Função melhorada para ler strings com segurança
void ler_string(char* destino, int tamanho) {
    fgets(destino, tamanho, stdin);
    destino[strcspn(destino, "\n")] = '\0'; // Remove o ENTER do final
}

int main() {
    Biblioteca bib;
    inicializar_biblioteca(&bib);

    adicionar_livro(&bib, "O Hobbit", "J.R.R. Tolkien");
    adicionar_livro(&bib, "Duna", "Frank Herbert");
    adicionar_livro(&bib, "Cujo", "Stephen King");

    int opcao = -1;
    char entrada[20];
    char titulo[MAX_STR];
    char usuario[MAX_STR];

    do {
        printf("\n=== SISTEMA DE BIBLIOTECA ===\n");
        printf("1. Listar Catalogo\n");
        printf("2. Pegar Livro Emprestado / Reservar\n");
        printf("3. Devolver Livro (Jogar na Caixa)\n");
        printf("4. Processar Caixa de Devolucoes (Pilha)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        
        // Forma muito mais segura de ler números em C para evitar bugs do Windows
        fgets(entrada, sizeof(entrada), stdin);
        if (sscanf(entrada, "%d", &opcao) != 1) {
            opcao = -1; // Se digitar letra sem querer, vira opção inválida
        }

        switch (opcao) {
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
                printf("Encerrando o sistema da biblioteca.\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    // Isso vai impedir o executável de fechar sozinho caso você dê 2 cliques!
    printf("\nPressione ENTER para fechar a janela...");
    getchar();

    return 0;
}