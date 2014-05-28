#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {
	int pp = open("/tmp/options", O_WRONLY, 0700);
	int n = 0;

	char *aux = "2:Braga:Braga:S.Vitor"; /* Fazer Menu Para Isto */
	char line[strlen(aux)+3];

	if(n==0) { //incrementar
		strcpy(line,"i:");
		strcat(line,aux);
	} else {	//agregar
		strcpy(line,"a:");
		strcat(line,aux);
	}
	write(pp, line, strlen(line));
	return 0;
}