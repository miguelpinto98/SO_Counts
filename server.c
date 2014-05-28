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

		Distrito d1 = criaDistrito("Porto",3214);
		insereDistrito(ll,d1);
		d1 = criaDistrito("Lisboa",123);
		insereDistrito(ll,d1);

	char buff[1024];
	int n, x = 0;
	int i=1;
	while(i<300000) {
		n = read(pp,buff,1024);

		char c = buff[0];
		char* res = removeID(buff);
		char* distritoNome = getString((buff+2),&x);

		d1 = verificaDistrito(ll,distritoNome);

		if(d1) {
			write(1,d1->nome,6);
		}

		//write(1,res,n);
		//write(1,dist,n);
		i++;
	}
	
	/*
	Distrito d2 = criaDistrito("Porto",3214);
	Distrito d3 = criaDistrito("Lisboa",3214);

	insereDistrito(ll,d1);
	insereDistrito(ll,d2);
	insereDistrito(ll,d3);

	printf("HELLO\n");
	lista(ll->elems);
	*/

	//printf("\n\n");
	//lista(ll->elems);
	return 0;
}