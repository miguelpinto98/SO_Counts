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
	char childBuffer[1024];
	int n, j=1, indice=0, fd;
	Distrito d = NULL;

	while(j) {
		n = read(pp,buff,1024);
		
		//char ch1 = buff[0];
		int in2 = getNumero((buff+2),&indice);
		char* distritoNome = getString((buff+4),&indice);

		if((d = verificaDistrito(ll,distritoNome)) != NULL) {
			close(d->fd[0]);
			write(d->fd[1],buff,n);
		} else {
			d = criaDistrito(distritoNome);
			insereDistrito(ll,d);

			int p = fork();
			if(p==0) {
				while(1) {
					close(d->fd[1]);
					read(d->fd[0],childBuffer,1024);
					write(1,childBuffer,1024);

					char ch1 = childBuffer[0];
					int in2 = getNumero((childBuffer+2),&indice);
					if(ch1=='i') {
						char *array[3];
						array[0] = strdup("Braga");
						array[1] = strdup("Braga");
						array[2] = strdup("S.Vitor");

						printf("%s\n", childBuffer);
						incrementar(array,in2);
					}


					exit(0); 
				}
			}
		}
	}
	return 0;
}