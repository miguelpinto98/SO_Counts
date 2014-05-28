#include "utils.h"

char *removeID(char *s) {
	return (s+2);
}

char *getString(char *buff, int *n) {
	int i;
	char *aux = malloc(strlen(buff));

	for(i=0; buff[i]!=':'; i++)
		aux[i] = buff[i];

	aux[i] = '\0';
	*n = i;

	return aux;
}

int getNumero(char *buff, int *n) {
	int i;
	char aux[10];
	
	for(i=0; buff[i]!=':'; i++) {
		aux[i] = buff[i];
	}
	aux[i] = '\n';
	*n = i;

	return atoi(aux);
}
/*
void closeFicheiro(int id) {
	close(id);
}*/