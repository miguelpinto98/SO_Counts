#include "struct.h"
#include "linkedlist/linkedlist.h"
#include "utils.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	int mk = mkfifo("/tmp/options",0666);
	int pp = open("/tmp/options", O_RDONLY, 0700);

	LinkedList ll = createLinkedList(NULL,NULL);

	char buff[1024];
	char line[1024];
	int n, j=1, indice=0, fd;

	while(j) {
		n = read(pp,buff,1024);
		
		char ch1 = buff[0];
		int in2 = getNumero((buff+2),&indice);
		char* distritoNome = getString((buff+4),&indice);

		fd = open(distritoNome, O_RDONLY | O_WRONLY, 0777);
		if(fd < 0) 

		/* Incrementar */
		if(ch1 == 'i') {
			
			
			/* Ficheiro nao existe */
			if(fd < 0) { 
				fd = open(distritoNome, O_WRONLY | O_CREAT, 0777);
				write(fd,(buff+4),strlen((buff+4)));
			} else {
				write(fd,(buff+4),strlen((buff+4)));
			}
			/*
			while((n = read(fd,line,1024)) > 0) {
				write(fd,(buff+4), strlen((buff+4)));
				printf("dadas\n");
			}	*/

			close(fd);		
		}

		/* Agregar */
		if(ch1 == 'a') { ; }
	}
	return 0;
}