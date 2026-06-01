typedef struct livro Livro;

Livro* criarLivro(Livro* inicio, char* titulo, char* genero, char* editora, char* autor, int ano);

Livro* criarListaLivros();

void imprimirLivros(Livro *lista);

void excluirlivros(Livro *lista);