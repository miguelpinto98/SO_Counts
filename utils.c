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

int incrementar(char *nome[], int valor) {
	int file;
	char* distritoNome = nome[0];
	file = open(distritoNome, O_RDWR, 0700);
	
	int xx=0, numLidos=0, chPorLer=0, inc=0, len=0, i=0, j;	

	if(file < 0) { 
		file = open(distritoNome, O_WRONLY | O_CREAT, 0777);
		char* line = malloc(100);
		sprintf(line,"%s:%s:%d\n",nome[1],nome[2],valor);
		write(file,line,strlen(line));
		close(file);
	} else {
		char* buffer = malloc(1024);
		xx = read(file,buffer,1024);
		//caso concelho-freguesia não exista
		if(strstr(buffer,nome[1]) == NULL) {
			char* new = malloc(100);
			sprintf(new,"%s:%s:%d\n",nome[1],nome[2],valor);
			write(file,new,strlen(new));
			close(file);
		} else {

			char* line = malloc(xx);
			sprintf(line,"%s:%s:",nome[1],nome[2]);
				
			inc = devolveValor(buffer,line,&numLidos,&chPorLer);
			inc += valor;

			len = int_len(inc);
			char n[len];
			len = sprintf(n,"%d",inc);

			char* pointer = strstr(buffer,line);
			int tam = strlen(line);
			pointer = pointer + tam;

			if(len == numLidos) {
				for(i=0; i < len; i++)
					pointer[i] = n[i];

				close(file);
				file = open(distritoNome, O_RDWR, 0700);
				write(file,buffer,strlen(buffer));
			} else {
				int diff = len-numLidos;
				char *aux = malloc(xx+diff);

				int aa = xx-chPorLer+tam;
				for(i=0; i<aa; i++)
					aux[i] = buffer[i];

				for(j=0; j<len; j++) {
					aux[i] = n[j];
					i++;
				}
				aux[i] = '\n'; i++;

				tam = strlen(pointer);
				for(j=numLidos+1; j<=tam; j++) {
					aux[i] = pointer[j];
					i++;
				}

				close(file);
				file = open(distritoNome, O_RDWR, 0700);
				write(file,aux,strlen(aux));
			}
		}
	}	
	return 1;
}

int devolveValor(char* buffer, char* search, int *n, int *x) {
	char* pointer = strstr(buffer,search);
	*x = strlen(pointer);
	
	int i, res=0;
	int tam = strlen(search);
	pointer = pointer + tam;
	
	if(pointer != NULL) {
		char numero[5];
		for (i = 0; pointer[i] != '\n'; i++) {
			numero[i] = pointer[i];
		}
		*n = i;
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
	array[1]="Amarante";
	array[2]="Cabrões";
	incrementar(array,1000);

	char* buffer = "Felgueiras:Revinhade:30\nFelgueiras:Torrados:20\nFelgueiras:Sousa:10";
	char* search = "Felgueiras:Torrados:";
	//printf("%d\n",devolveValor(buffer,search));
	return 1;
}