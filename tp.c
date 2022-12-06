#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAM 257
#define PONTOS " ,.!-?/;:\n"

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

// Função para colocar todos os caracteres da string minúsculos

void minuscula(char str[]) {
    int tam = strlen(str);
    for(int i = 0; i < tam; i++) {
        str[i] = tolower(str[i]);
    }
}

int inserir(TabelaHash t[], char chave[]) {
    minuscula(chave);
    if(strlen(chave) > 1) {
        int id = funcaoHashString(chave); // Conseguindo a posição na qual a string será inserida.
        while(strlen(t[id].str) > 1) {    // Se houver colisão, isto é, houver uma string nesse
            if(strcmp(t[id].str, chave) == 0) {  // local, veremos se é a mesma string que será
                t[id].frequencia++;              // inserida. Se for, não adicionaremos ela na
                return 0;                        // tabela. Se não for, procuraremos a próxima
            }                                    // posição vazia para adicioná-la.
            else {     
                id = funcaoHash(id + 1);
            }       
        }                                 
        strcpy(t[id].str, chave);
        t[id].frequencia++;
    }
}

TabelaHash *busca(TabelaHash t[], char chave[]) {
    minuscula(chave);
    int id = funcaoHashString(chave);
    //printf("Indice: %d\n", id);
    while(strlen(t[id].str) > 1) {
        if(strcmp(t[id].str, chave) == 0) {
            return &t[id];
        }
        id = funcaoHash(id + 1);
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
        TabelaHash *buscar, tabela[TAM];
        int linhas = 1;

        FILE *entrada;
        entrada = fopen("input.txt", "r");

        FILE *pesquisa;
        pesquisa = fopen("pesquisa.txt", "r");

        inicializar(tabela);

        if(entrada == NULL) {
            printf("Não foi possivel encontrar o arquivo.\n");
            exit(1);
        }

        // Lendo o arquivo de entrada.

        char linhaInteira[81];
    
        while(fgets(linhaInteira, 80, entrada) != NULL) {
            char* palavraSozinha = strtok(linhaInteira, PONTOS);
            while (palavraSozinha != NULL) {
                inserir(tabela, palavraSozinha);  // colocar linha como parametro    
                palavraSozinha = strtok(NULL, PONTOS);
            }
        }

        // Pesquisando as palavras por meio do arquivo pesquisa.txt.

        if(pesquisa == NULL) {
            printf("Não foi possivel encontrar o arquivo.\n");
            exit(1);
        }

        char palavra[50];
        int flag = 0; /*Variável flag para iniciar lendo o arquivo a partir das palavras (ignorando a primeira linha) */        
        while(fgets(palavra, 49, pesquisa) != NULL) {
            if (!flag) {
                    flag = 1;
                    continue;
            }
                    
            if (palavra[strlen(palavra)-1] == '\n') {
                palavra[strlen(palavra)-1] = '\0';
            }
            minuscula(palavra);
            buscar = busca(tabela, palavra);
            if(buscar != NULL) {
                printf("%d ", buscar->frequencia);
                printf("%s \n", palavra);
            }
            setbuf(stdin, NULL);
        }

        imprimir(tabela);

        fclose(entrada);
        fclose(pesquisa);
}
