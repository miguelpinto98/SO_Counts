#include "struct.h"

/*
void* getNomeDistrito(void* dist) {
	return strdup(dist->nome);
}

int comparaDistritos(void* dist1, void* tit2) {
	char * s1 = strdup(dist1->nome);
	char * s2 = strdup(dist2->nome);

	return strcmp(s1,s2);
}

LinkedList iniciaDistritos() {
	return createLinkedList(getNomeDistrito,comparaDistritos);
}*/

void insereDistrito(LinkedList lpages, Distrito d) {
	pushLinkedList(lpages, d);
}

Distrito criaDistrito(char *nm, int p) {
	Distrito dist = NULL;

	dist = (Distrito)malloc(sizeof(NDistrito));
	dist->nome = strdup(nm);
	dist->pid = p;
	dist->nagrupada = 0;

	return dist; 
}

void lista(LinkedElem ll) {
	LinkedElem aux = ll;
	
	while(aux) {
		Distrito d = (Distrito) aux->data;

		printf("%s - %d\n",d->nome,d->pid);

		aux = aux->next;
	}
}