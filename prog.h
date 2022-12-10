// Estrutura usada para a Tabela Hash:

typedef struct {
    char str[50];
    int frequencia;
    int pri;  // Variável usada para armazenar a frequência da primeira ocorrência.
    int linhas[256]; // Array usado para armazenar as linhas em que uma palavra aparece.
}TabelaHash;

void inicializar(TabelaHash t[]);

int funcaoHash(int chave);

int funcaoHashString(char str[]);

void minuscula(char str[]);

int inserir(TabelaHash t[], char chave[], int linhas);

TabelaHash *busca(TabelaHash t[], char chave[]);

void imprimir(TabelaHash t[]);