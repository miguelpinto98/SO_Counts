#include "linkedlist/linkedlist.h"
#include "struct.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

char* removeID(char* ) ;

char* getString(char* , int*) ;

int getNumero(char *, int *) ;

int incrementar(char **, int ) ;

int agregar(char**, int , char*) ;

void preparaPedido(char *, LinkedList) ;

int somatorio(char *);