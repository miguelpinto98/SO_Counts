#include "utils.h"
#include "struct.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

LinkedList ll = NULL;

char *removeID(char *s) {
	return (s+2);
}

char *getString(char *buff, int *n) {
	int i;
	int tam = strlen(buff);
	char *aux = malloc(strlen(buff));

	for(i=0; buff[i]!=':'; i++)
		aux[i] = buff[i];

	aux[i] = '\0';
	*n = i+1;

	return aux;
}

char *getStringLast(char *buff, int *n) {
	int i;
	int tam = strlen(buff);
	char *aux = malloc(strlen(buff));

	for(i=0; i<tam; i++)
		aux[i] = buff[i];

	aux[i] = '\0';
	*n = i+1;

	return aux;
}

int getNumero(char *buff, int *n) {
	int i;
	char aux[10];
	
	for(i=0; buff[i]!=':'; i++) {
		aux[i] = buff[i];
	}
	aux[i] = '\n';
	*n = i+1;

	return atoi(aux);
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

int somatorio(char* buffer) {
	int res=0, i = 0;
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

int int_len (int value){
  int l=1;
  while(value>9){ l++; value/=10; }
  return l;
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

int incrementar(char *nome[], int valor) {
	
	Distrito d = NULL;
	d = verificaDistrito(ll,nome[0]);
	d->agregado += valor;
	int file;
	char* distritoNome = nome[0];
	file = open(distritoNome, O_RDWR, 0700);
	
	int xx=0, numLidos=0, chPorLer=0, inc=0, len=0, i=0, j;	

	if(file < 0) { 
		file = open(distritoNome, O_WRONLY | O_CREAT, 0777);
		char* line = malloc(100);
		sprintf(line,"%s:%s:%s:%d\n",nome[0],nome[1],nome[2],valor);
		write(file,line,strlen(line));
		free(line);
		close(file);
	} else {
		char* buffer = malloc(1024);
		xx = read(file,buffer,1024);
		//caso concelho-freguesia não exista
		if(strstr(buffer,nome[1]) == NULL) {
			char* new = malloc(100);
			sprintf(new,"%s:%s:%s:%d\n",nome[0],nome[1],nome[2],valor);
			write(file,new,strlen(new));
			free(new);
			close(file);
		}
		char* line = malloc(xx);
		sprintf(line,"%s:%s:%s:",nome[0],nome[1],nome[2]);
		if(strstr(buffer,line) == NULL) {
			char* new = malloc(100);
			sprintf(new,"%s:%s:%s:%d\n",nome[0],nome[1],nome[2],valor);
			write(file,new,strlen(new));
			free(new);
			close(file);
		} 
		else {
			char* line = malloc(xx);
			sprintf(line,"%s:%s:%s:",nome[0],nome[1],nome[2]);
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
				free(aux);
			}
			free(line);
		}
		free(buffer);
	}	
	return 1;
}

int tamanho(char* prefixo[]) {
	int i = 0;
	while(prefixo[i] != NULL) {
		i++;
	}

	return i;
}

int agregar(char* prefixo[], int nivel, char* path) {
	int size = tamanho(prefixo);
	if(size == 0) {
	}
	if(size == 1) {
		agregaUm(prefixo,nivel,path);
	}
	if(size == 2) {
		agregaDois(prefixo,nivel,path);
	}
	if(size == 3) {
		agregaTres(prefixo,nivel,path);
	}
}

int agregaUm(char* prefixo[], int nivel, char* path) {
	int file, distrito, xx = 0, i = 0, j = 0;
	file = open(path, O_WRONLY | O_CREAT, 0777);
	if(nivel == 0) {
		char* agregacao = malloc(100);
		Distrito d = NULL;
		d = verificaDistrito(ll,prefixo[0]);
		int total = d->agregado;
		sprintf(agregacao,"%s:%d\n",prefixo[0],2);
		write(file,agregacao,strlen(agregacao));
		close(file);
		free(agregacao);
	}
	if(nivel == 1) {
		char* visitados = malloc(100);
		distrito = open(prefixo[0],O_RDWR,0700);
		char* buffer = malloc(1024);
		xx = read(distrito,buffer,1024);
		i = 0;
		close(distrito);
		int n = contaN(buffer);
		while(i < n) {
			char* pointer = strstr(buffer,prefixo[0]);
			int inc = strcspn(pointer,"\n");
			pointer = pointer + strlen(prefixo[0]) + 1;
	
			int indice = strcspn(pointer,":");
			char* auxCon = malloc(100);
			strncpy(auxCon,pointer,indice);
			if( (strstr(visitados,auxCon)) == NULL) {
				strcat(visitados,auxCon);
				printf("%s\n",auxCon);
				agregacaoConcelho(auxCon,prefixo[0],file);
			}
			buffer = buffer + inc;
			i++;
		}
	}
	if(nivel == 2) {
		distrito = open(prefixo[0],O_RDWR,0700);
		char* buffer = malloc(1024);
		xx = read(distrito,buffer,1024);
		close(distrito);
		write(file,buffer,xx);
		close(file);
		free(buffer);
	}
	return 1;
}

int agregacaoConcelho(char* concelho, char* dis, int file) {
//Distrito:Concelho:200
	int xx = 0, i = 0, j = 0;
	int distrito = open(dis,O_RDWR,0700);
	char* buffer = malloc(1024);
	char* bufferAux = malloc(1024);
	int total=0;
	xx = read(distrito,buffer,1024);
	close(distrito);
	char* nome = malloc(200);
	char* tot = malloc(10);
	sprintf(nome,"%s:%s:",dis,concelho);
	int n=contaN(buffer);
	while((strstr(buffer,nome))!= NULL){
		char* pointer = strstr(buffer,nome);
		int ind0 = strcspn(pointer,"\n");
		pointer=pointer+strlen(dis)+strlen(concelho)+2;
		int ind1 = strcspn(pointer,":");
		pointer=pointer+ind1+1;
		char* valor = malloc(10);
		int ind2 = strcspn(pointer,"\n");
		strncpy(valor,pointer,ind2);
		int val = atoi(valor);
		total = total + val;
		sprintf(tot,"%d\n",total);
			while(buffer[i]!='\n'){
				i++;
			}
			buffer = buffer+i+2;
	}
	strcat(nome,tot);
	write(file,nome,strlen(nome));

	return 1;
}

int agregaDois(char* prefixo[], int nivel, char* path) {
	int file, distrito, xx = 0, i = 0, j = 0;
	file = open(path, O_WRONLY | O_CREAT, 0777);
	
	if(nivel == 0) {
		//Distrito:Concelho:200
		distrito = open(prefixo[0],O_RDWR,0700);
		char* buffer = malloc(1024);
		char* bufferAux = malloc(1024);
		int total=0;
		xx = read(distrito,buffer,1024);
		close(distrito);
		char* nome = malloc(200);
		char* tot = malloc(10);
		sprintf(nome,"%s:%s:",prefixo[0],prefixo[1]);
		int n=contaN(buffer);
		while((strstr(buffer,nome))!= NULL){
			char* pointer = strstr(buffer,nome);
			int ind0 = strcspn(pointer,"\n");
			pointer=pointer+strlen(prefixo[0])+strlen(prefixo[1])+2;
			int ind1 = strcspn(pointer,":");
			pointer=pointer+ind1+1;
			char* valor = malloc(10);
			int ind2 = strcspn(pointer,"\n");
			strncpy(valor,pointer,ind2);
			int val = atoi(valor);
			total = total + val;
			sprintf(tot,"%d\n",total);
				while(buffer[i]!='\n'){
					i++;
				}
				buffer = buffer+i+2;
		}
		strcat(nome,tot);
		write(file,nome,strlen(nome));

	}

	if(nivel == 1) {
		//Distrito:Concelho:Freguesias:Valor
		distrito = open(prefixo[0],O_RDWR,0700);
		char* buffer = malloc(1024);
		char* bufferAux = malloc(1024);
		xx = read(distrito,buffer,1024);
		close(distrito);
		int pos;
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
			free(line);
		}

		write(file,bufferAux,strlen(bufferAux));
		close(file);
		free(buffer);
		free(bufferAux);
	}
	return 1;
}

int agregaTres(char* prefixo[], int nivel, char* path) {
	int file, distrito, xx = 0, i = 0, j = 0;
	file = open(path, O_WRONLY | O_CREAT, 0777);
	
	if(nivel == 0) {
		//Distrito:Concelho:Freguesia:Valor
		distrito = open(prefixo[0],O_RDWR,0700);
		char* buffer = malloc(1024);
		xx = read(distrito,buffer,1024);
		close(distrito);
		char* nome = malloc(200);
		sprintf(nome,"%s:%s:%s:",prefixo[0],prefixo[1],prefixo[2]);
		char* pointer = strstr(buffer,nome);
		int ind = strcspn(pointer,"\n");
		strncpy(nome,pointer,ind+1);
		write(file,nome,strlen(nome));
		close(file);
		free(buffer);
		free(nome);
		}
	return 1;
}

void preparaPedido(char *buffer, LinkedList list) {
	ll = list;
	int lidos = 0, tam = 2;
	char *array[3];
	
	char tipo = buffer[0];
	int valor = getNumero(buffer+tam,&lidos);
	tam += lidos;

	array[0] = strdup(getString(buffer+tam,&lidos));
	tam += lidos;
	
	array[1] = strdup(getString(buffer+tam,&lidos));
	tam += lidos;
	
	if(tipo == 'i'){
		array[2] = strdup(getStringLast(buffer+tam,&lidos));

		incrementar(array,valor);
	}
	else {
		array[2] = strdup(getString(buffer+tam,&lidos));
		tam += lidos;

		char *str = strdup(getStringLast(buffer+tam,&lidos));

		agregar(array,valor,str);
	}
}

