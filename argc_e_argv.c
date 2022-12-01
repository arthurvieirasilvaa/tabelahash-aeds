#include <stdio.h>

int main (int argc, char *argv[]){
	if (argc < 3)
		printf("Faltam parametros. Sao necessarios 2 arquivos para executar corretamente.\n");
	else if (argc > 3)
		printf("Parametros demais. Sao necessarios somente 2 arquivos.\n");
	else //if (argc == 3)
		printf ("Parabens, voce executou corretamente o codigo:\n%s %s %s\n", argv[0], argv[1], argv[2]);

	return 0;
}
