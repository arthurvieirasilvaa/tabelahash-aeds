#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAM 257
#define PONTOS " ,.!-?/;:\n"

// Estrutura usada para mostrar em quais linhas uma palavra aparece:

typedef struct mostralinha {
    int linha;
    struct mostralinha *prox;
}MostraLinha;

// Estrutura usada para a Tabela Hash:

typedef struct {
    char str[50];
    int frequencia;
    MostraLinha *pri;
}TabelaHash;

// Função usada para encontrar a linha da primeira ocorrência da palavra.

MostraLinha *PrimeiraOcorrencia(int linha) {
    MostraLinha* novo = (MostraLinha*) malloc(sizeof(MostraLinha));

    novo->linha = linha;
    novo->prox = NULL;
    return novo;
}

// Função para verificar em quais linhas estão as outras palavras da ocorrência.

void NovaOcorrencia(TabelaHash *t, int linha) {
    MostraLinha **aux = &t->pri;

    if(*aux != NULL) {
        while((*aux)->prox != NULL) {
            aux = &((*aux)->prox);
        }

        if(linha != (*aux)->linha) {
            (*aux)->prox = PrimeiraOcorrencia(linha);
        }
        t->frequencia++;
    }

    else {
        *aux = PrimeiraOcorrencia(linha);
        t->frequencia = 1;
    }
}

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

/*
    Conseguindo a posição na qual a string será inserida. Se houver colisão, isto é, houver uma string nesse local, veremos se é a mesma string que será inserida. Se for, não adicionaremos ela na tabela. Se não for, procuraremos a próxima posição vazia para adicioná-la.
*/

int inserir(TabelaHash t[], char chave[], MostraLinha linhas) {
    minuscula(chave);
    int id = funcaoHashString(chave);
    if(strlen(chave) > 1) {
        while(strlen(t[id].str) > 1) {   
            if(strcmp(t[id].str, chave) == 0) {                 
                t[id].frequencia++;
                return 0;
            }        
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
        MostraLinha *linhas;
        char palavra[50];

        FILE *entrada;
        entrada = fopen("input.txt", "r");

        FILE *pesquisa;
        pesquisa = fopen("pesquisa.txt", "r");

        inicializar(tabela);

        if(entrada == NULL) {
            printf("Não foi possivel encontrar o arquivo.\n");
            exit(1);
        }

        char linhaInteira[81];

        // Lendo o arquivo de entrada.
    
        while (fgets(linhaInteira, 80, entrada) != NULL) {
            if(linhaInteira[strlen(linhaInteira)-1] == '\n') {
                linhas->linha++;
            }
            char* palavraSozinha = strtok(linhaInteira, PONTOS);
            while (palavraSozinha != NULL) {
                inserir(tabela, palavraSozinha, *linhas);  // colocar linha como parametro    
                palavraSozinha = strtok(NULL, PONTOS);
            }
        }

        // Pesquisando as palavras por meio do arquivo pesquisa.txt.

        if(pesquisa == NULL) {
            printf("Não foi possivel encontrar o arquivo.\n");
            exit(1);
        }

        /* Variável flag para iniciar lendo o arquivo a partir das palavras (ignorando a primeira linha) */

        int flag = 0;         

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
                printf("%s ", palavra);

                if(buscar->frequencia == 1) {
                    linhas = PrimeiraOcorrencia(buscar->pri->linha);
                    printf("%d ", linhas->linha);
                }
                printf("\n");
            }

            // Se a palavra não estiver na tabela, a sua frequência será 0 e a função busca
            // retorna NULL.
    
            else{
                printf("0 "); 
                printf("%s \n", palavra);
                // Não há a indicação das linhas pois, a palavra não está no texto.
            }
        }

        //imprimir(tabela);

        fclose(entrada);
        fclose(pesquisa);
}