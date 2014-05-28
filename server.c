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

	int pp = open("/tmp/options", O_RDONLY, 0700);
	char buff[1024];

	while(1) {
		n = read(pp,buff,1024);
		
		char c = buff[0];
		char* res=removeID(buff);
		
		write(1,res,n);
	}

	Distrito d1 = criaDistrito("Braga",3214);
	Distrito d2 = criaDistrito("Porto",3214);
	Distrito d3 = criaDistrito("Lisboa",3214);

	insereDistrito(ll,d1);
	insereDistrito(ll,d2);
	insereDistrito(ll,d3);

	printf("HELLO\n");
	lista(ll->elems);

	return 0;
}