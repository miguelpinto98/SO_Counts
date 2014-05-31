#include "utils.h"
#include "struct.h"
#include "linkedlist/linkedlist.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

int agregar(char* prefixo[], int nivel, char* path) {
	int file, distrito, i = 0, xx = 0, pos = 0, j = 0;
	file = open(path, O_WRONLY | O_CREAT, 0777);

	if(nivel == 0) {
		distrito = open(prefixo[0], O_RDWR, 0700);
		char* buffer = malloc(1024);
		read(distrito,buffer,1024);
		close(distrito);

		write(file,buffer,strlen(buffer));

		int total = somatorio(buffer);
		char* agregacao = malloc(100);
		sprintf(agregacao,"\nTOTAL:%d\n",total);
		write(file,agregacao,strlen(agregacao));
		close(file);
	}
	if (nivel == 1) {
		distrito = open(prefixo[0],O_RDWR,0700);
		char* buffer = malloc(1024);
		char* bufferAux = malloc(1024);
		xx = read(distrito,buffer,1024);
		close(distrito);
		char* concelho = prefixo[1];
		while(j < contaN(buffer)) {
			char* line = malloc(100);
			pos = 0;
			while(buffer[i] != '\n') {
				line[pos] = buffer[i];
				pos++;
				i++;
			}
			line[pos] = '\n';
			i++;
			char* pointer = strstr(line,concelho);
			if(pointer != NULL) {
				strcat(bufferAux,line);
			}
			j++;
		}
		write(file,bufferAux,strlen(bufferAux));

		int total = somatorio(bufferAux);
		char* agregacao = malloc(100);
		sprintf(agregacao,"\nTOTAL:%d\n",total);
		write(file,agregacao,strlen(agregacao));
		close(file);
	}
	return 1;
}

int somatorio(char* buffer) {
	int res, i = 0;
	char *p = buffer;
	int len = contaN(buffer);
	int somatorio[len];
	while (*p) {
		if (isdigit(*p)) {
			long val = strtol(p, &p, 10);
			somatorio[i] = val;
			res = res + somatorio[i];
		} else {
			p++;
		}
	}
	return res;
}

int contaN(char* buffer) {
	int res=0;
	int i=0;
	while(buffer[i] != '\0') {
		if(buffer[i] == '\n')
			res++;
		i++;
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
	//incrementar(array,1000);
	char* agrega[2];
	agrega[0] = "Porto";
	agrega[1] = "Felgueiras";
	agregar(agrega,1,"Agrega_Felgueiras");
	char* buffer = "Felgueiras:Revinhade:30\nFelgueiras:Torrados:20\nFelgueiras:Sousa:10\n";
	char* search = "Felgueiras:Torrados:";
	//printf("%d\n",devolveValor(buffer,search));
	//somatorio(buffer);
	return 1;
}