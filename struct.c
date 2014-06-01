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

int searchFunction(void *distrito, void *nome) {
	Distrito d = (Distrito) distrito;
	char *str = (char *) nome;

	if(strcmp(d->nome,nome)==0)
		return 1;

	return 0;
} 

Distrito verificaDistrito(LinkedList list, char *nome) {
	return searchLinkedList(list, searchFunction, nome);
}

void insereDistrito(LinkedList ll, Distrito d) {
	pushLinkedList(ll, d);
	printf("Inseri %s\n", d->nome);
}

Distrito criaDistrito(char *nm) {
	Distrito dist = NULL;
	int leu;
	dist = (Distrito)malloc(sizeof(NDistrito));
	dist->nome = strdup(nm);
	pipe(dist->fd);

	leu = open(nm,O_RDWR,0700);
	if(leu > 0) {
		char* buffer = malloc(1024);
		read(leu,buffer,1024);

		int total = somatorio(buffer);
		dist->agregado = total;
		free(buffer);
	}
	else {
		dist->agregado = 0;
	}


	return dist; 
}
/*
void lista(LinkedElem ll) {
	LinkedElem aux = ll;
	
	while(aux) {
		Distrito d = (Distrito) aux->data;

		printf("%s - %d\n",d->nome,d->pid);

		aux = aux->next;
	}
}*/