#include "struct.h"
#include "linkedlist/linkedlist.h"
#include <stdio.h>

int main()
{
	LinkedList ll = createLinkedList(NULL,NULL);

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