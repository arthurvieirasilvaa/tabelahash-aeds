#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAM 521
#define PONTOS " ,.!-?/;:\n"
#include "prog.h"

void main() {
        TabelaHash *buscar, tabela[TAM];
        int linhas = 1;
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

        /* 
            Lendo o arquivo de entrada e utilizando strtok para retirar pontuações, espaços
            em branco e quebras de linha. 
        */
    
        while (fgets(linhaInteira, 80, entrada) != NULL) {
            if(linhaInteira[strlen(linhaInteira)-1] == '\n') {
                linhas++;
            }
            char* palavraSozinha = strtok(linhaInteira, PONTOS);
            while (palavraSozinha != NULL) {
                inserir(tabela, palavraSozinha, linhas);
                palavraSozinha = strtok(NULL, PONTOS);
            }
        }

        // Pesquisando as palavras por meio do arquivo pesquisa.txt.

        if(pesquisa == NULL) {
            printf("Não foi possivel encontrar o arquivo.\n");
            exit(1);
        }

        /* 
            Variável flag para iniciar lendo o arquivo a partir das palavras (ignorando a primeira linha).
        */

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
                    printf("%d ", buscar->pri);
                }

                else {
                    printf("%d ", buscar->pri);
                    for (int i = 1; i < buscar->frequencia; i++) {
                        if(buscar->linhas[i] != 0) {
                            printf("%d ", buscar->linhas[i]);
                        }
                    }
                }
                printf("\n");
            }

            /*
                Se a palavra não estiver na tabela, a sua frequência será 0 e a função busca
                retorna NULL.
            */
    
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