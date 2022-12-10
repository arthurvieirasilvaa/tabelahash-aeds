#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAM 521
#define PONTOS " ,.!-?/;:\n"
#include "prog.h"

// Função para inicializar a tabela com espaços vazios:

void inicializar(TabelaHash t[]) {
    for(int i = 0; i < TAM; i++) {
        t[i].frequencia = 0;
        t[i].linhas[i] = 0;
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

int inserir(TabelaHash t[], char chave[], int linhas) {
    minuscula(chave);
    int id = funcaoHashString(chave);
    if(strlen(chave) > 1) {
        while(strlen(t[id].str) > 1) {   
            if(strcmp(t[id].str, chave) == 0) {                
                t[id].frequencia++;
                for (int i = 0; i < 256; i++) {
                    if(t[id].linhas[i] == 0) {
                        t[id].linhas[i] = linhas;
                    }
                }
                return 0;
            }        
            else {     
                id = funcaoHash(id + 1);
            }                       
        }                                                              
        strcpy(t[id].str, chave);
        t[id].frequencia++;
        t[id].pri = linhas;
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