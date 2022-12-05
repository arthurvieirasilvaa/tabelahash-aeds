#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 257
#define ACENTOS ",.!-"

// Estrutura usada para a Tabela Hash:

typedef struct {
    char str[50];
    int frequencia;
}TabelaHash;

// Função para inicializar a tabela com espaços vazios:

void inicializar(TabelaHash t[]) {
    for(int i = 0; i < TAM; i++) {
        t[i].frequencia = 0;
        strcpy(t[i].str, "");
    }
}

// Função hash utilizada para tratar as colisões: 

int funcaoHash(int chave) {
    return chave % TAM;
}

// Cálculo do hash da string para inserção na tabela.
// A variável hash recebe o código ASCII do caractere na posição i multiplicado pela posição i + 1.

int funcaoHashString(char str[]) {
    int tamstr = strlen(str);
    unsigned int hash = 0;
    for(int i = 0; i < tamstr; i++) {
        hash += str[i] * (i + 1);
    }
    return hash % TAM;
}

void inserir(TabelaHash t[], char chave[]) {
    strupr(chave);
    if(strlen(chave) > 2) {
        int id = funcaoHashString(chave); // Conseguindo a posição na qual a string será inserida.
        while(strlen(t[id].str) > 1) {    //Se houver colisão, isto é, 
            id = funcaoHash(id + 1);      // houver uma string nesse local, 
        }                                 // iremos para a próxima posição da tabela.
        strcpy(t[id].str, chave);
    }
}

TabelaHash *busca(TabelaHash t[], char chave[]) {
    strupr(chave);
    int id = funcaoHashString(chave);
    printf("Indice gerado: %d\n", id);

    for(int i = 0; i < TAM; i++) {          // Laço for para calcular a frequência 
        if(strcmp(chave, t[i].str) == 0) {  // com que a palavra aparece.
            t[id].frequencia++;
        }
    }

    while(strlen(t[id].str) > 1) {
        if(strcmp(t[id].str, chave) == 0) {
            return &t[id];
        }
        else {
            id = funcaoHash(id + 1);
        }
    }
    return NULL;   
}

void imprimir(TabelaHash t[]) {
    for(int i = 0; i < TAM; i++) {
        printf("%d = ", i);
        printf("%s\n", t[i].str);
    }
}

void main() {
        TabelaHash *buscar, tabela[TAM], aux[TAM];
        char nome[50];
        int opcao, i = 0, j = 0, linhas = 1;
        int num = 0;

        FILE *entrada;
        entrada = fopen("input.txt", "r");

        FILE *pesquisa;
        pesquisa = fopen("pesquisa.txt", "r");

        inicializar(tabela);

        if(entrada == NULL) {
            printf("Não foi possivel encontrar o arquivo.\n");
        }

        // Lendo o arquivo de entrada.

        else {
            while(!feof(entrada)) {
                nome[i] = fgetc(entrada);
                if(nome[i] == ' ') {
                    if(strlen(nome) > 1) {
                        nome[i] = '\0';
                        inserir(tabela, nome);
                        i = -1;  
                    }
                }
                if(nome[i] == '\n') {
                    linhas++;
                }
                ++i;
            }
        }

        // Pesquisando as palavras por meio do arquivo pesquisa.txt.

        if(pesquisa == NULL) {
            printf("Não foi possivel encontrar o arquivo.\n");
        }

        else {
            while(!feof(pesquisa)) {
                fscanf(pesquisa, "%d", &num);
                for(int i = 0; i < num; i++) {
                    fgets(nome, 49, pesquisa);
                    buscar = busca(tabela, nome);
                    if(buscar != NULL) {
                        printf("\nNome encontrado: ");
                        printf("%s\n", buscar->str);
                        printf("Frequencia: %d\n", buscar->frequencia);
                    }
                    else {
                        printf("Nome nao encontrado!\n");
                    }
                    setbuf(stdin, NULL);
                }
            }
        }

        imprimir(tabela);

        /*

        printf("Digite o nome que deseja buscar: ");
        scanf("%s", nome);
        buscar = busca(tabela, nome);
        if(buscar != NULL) {
            printf("\nNome encontrado: ");
            printf("%s\n", buscar->str);
            printf("Frequencia: %d\n", buscar->frequencia);
        }
        else {
            printf("Nome nao encontrado!\n");
        }
        setbuf(stdin, NULL);

        */

        fclose(entrada);
        fclose(pesquisa);

        /*
        do {
            printf("\n===============\n");
            printf("MENU DE OPCOES\n");
            printf("===============\n");
            printf("\n0 - SAIR\n1 - Inserir\n2 - Buscar\n3 - Imprimir\n");
            printf("Digite uma opcao: ");
            scanf("%d", &opcao);
            setbuf(stdin, NULL);

            switch(opcao) {
                case 1: 
                    printf("Digite o nome que deseja inserir: ");
                    fgets(nome, 49, stdin);
                    strupr(nome);
                    if(strlen(nome) > 2) {
                        inserir(tabela, nome);
                    }
                    setbuf(stdin, NULL);
                    break;
                case 2:
                    printf("Digite o nome que deseja buscar: ");
                    fgets(nome, 49, stdin);
                    strupr(nome);
                    buscar = busca(tabela, nome);
                    if(buscar != NULL) {
                        printf("\nNome encontrado: ");
                        printf("%s\n", buscar->str);
                    }
                    else {
                        printf("Nome nao encontrado!\n");
                    }
                    setbuf(stdin, NULL);
                    break;
                case 3:
                    imprimir(tabela);
                    break;
                default:
                    if(opcao != 0) {
                        printf("Opcao invalida!\n");
                    }
            }
        }while(opcao != 0);
    */
}
