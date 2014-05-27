#ifndef __STRUCT
#define __STRUCT

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "linkedlist/linkedlist.h"

typedef struct sDistrito {
	char* nome;
	int pid;
	int nagrupada;
} *Distrito, NDistrito;

void insereDistrito(LinkedList, Distrito) ;

Distrito criaDistrito(char *, int) ;

void lista(LinkedElem) ;

#endif