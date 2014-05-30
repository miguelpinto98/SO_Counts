#include "utils.h"
#include <fcntl.h>

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

//Porto:Felgueiras:Revinhade
int incrementar(char *nome[], int valor) {
	int file;
	char* distritoNome = nome[0];
	file = open(distritoNome, O_RDWR, 0700);

	if(file < 0) { 
				file = open(distritoNome, O_WRONLY | O_CREAT, 0777);
				char* line = malloc(100);
				sprintf(line,"%s:%s:%d",nome[1],nome[2],valor);
				write(file,line,strlen(line));
				close(file);
			} else {
				char* buffer = malloc(1024);
				read(file,buffer,1024);
				char* line = malloc(100);
				sprintf(line,"%s:%s:",nome[1],nome[2]);
				int inc = devolveValor(buffer,line);
				inc = inc + valor;
				int len = int_len(inc);
				char n[len];
				sprintf(n,"%d",inc);
				int i = 0;
				/*if(int_len(inc) > int_len(valor)) {
				}*/
				//se ultrapassar 100, nao da.
				//falta fazer shift
				char* pointer = strstr(buffer,line);
				int tam = strlen(line);
				pointer = pointer + tam;
				while(pointer[i] != '\n') {
						pointer[i] = n[i];
						i++;
					}
				pointer[i] = n[i];
				pointer[i+1] = '\0';
				close(file);
				file = open(distritoNome, O_RDWR, 0700);
				write(file,buffer,strlen(buffer));
			}	
	return 1;
}

int devolveValor(char* buffer, char* search) {
	char* pointer = strstr(buffer,search);
	int i;
	int res=0;
	int tam = strlen(search);
	pointer = pointer + tam;
	if(pointer != NULL) {
		char numero[5];
		for (i = 0; pointer[i] != '\n'; i++) {
			numero[i] = pointer[i];
		}
		numero[i] = '\0';
		res = atoi(numero);
	}
	return res;
}

int int_len (int value){
  int l=1;
  while(value>9){ l++; value/=10; }
  return l;
}

int main() {
	char* array[3];
	array[0]="Porto";
	array[1]="Felgueiras";
	array[2]="Revinhade";
	incrementar(array,30);

	char* buffer = "Felgueiras:Revinhade:30\nFelgueiras:Torrados:20\nFelgueiras:Sousa:10";
	char* search = "Felgueiras:Torrados:";
	//printf("%d\n",devolveValor(buffer,search));
	return 1;
}