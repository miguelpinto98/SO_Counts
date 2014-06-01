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
	
	LinkedList ll = createLinkedList(NULL,NULL);

	char buff[1024];
	char childBuffer[1024];
	int n, j=1, indice=0, fd, tam=0;
	Distrito d = NULL;

	while(j) {
		int pp = open("/tmp/options", O_RDONLY, 0700);
		n = read(pp,buff,1024);
		close(pp);

		int in = getNumero((buff+2),&indice);
		tam = 2 + indice;
		char* distritoNome = getString((buff+tam),&indice);

		if((d = verificaDistrito(ll,distritoNome)) != NULL) {
			write(d->fd[1],buff,n);
		} else {
			d = criaDistrito(distritoNome);
			insereDistrito(ll,d);

			int p = fork();
			if(p==0) {
				int x = 0;
				while(1) {
					close(d->fd[1]);
					x=read(d->fd[0],childBuffer,1024);
					
					printf("Antes\n");
					preparaPedido(childBuffer,x);
					printf("Depois\n");
				}
			} else {
				close(d->fd[0]);
				write(d->fd[1],buff,n);
				//close(d->fd[0]);
			}
		}
	}
	return 0;
}