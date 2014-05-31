#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* menuInicio(){
	char* s = malloc(50);
	char* menu = strdup("###################################\n#                                 #\n# 1 - Incrementar                 #\n# 2 - Agregar                     #\n#                                 #\n###################################\n");
	int r;
	write(1,menu,strlen(menu));
	r=read(0,s,50);

	if(!((s[0]=='1') || (s[0]=='2')))
		s="erro";
	return s;
}

char* menuIncrementar(){
	char* res = malloc(1024);
	int r1,r2,r3,r4;
	char* distrito = malloc(100);
	char* concelho = malloc(100);
	char* freguesia = malloc(100);
	char* numInc = malloc(100);
	char* distritoAux = malloc(100);
	char* concelhoAux = malloc(100);
	char* freguesiaAux = malloc(100);
	char* numIncAux = malloc(100);
	char* menu = strdup("################################\n#         Incrementar          #\n#                              #\n# Em que distrito?             #\n");
	write(1,menu,strlen(menu));
	r1=read(0,distritoAux,100);
	printf("%s\n", distritoAux);
	while(r1==1){
		char* dist = strdup("# Em que distrito?             #\n");
		write(1,dist,strlen(dist));
		r1=read(0,distritoAux,100);
	}
	char* conc = strdup("# Em que concelho?             #\n");
	write(1,conc,strlen(conc));
	r2=read(0,concelhoAux,100);
	while(r2==1){
		write(1,conc,strlen(conc));
		r2=read(0,concelhoAux,100);
	}
	char* freg = strdup("# Em que freguesia?            #\n");
	write(1,freg,strlen(freg));
	r3=read(0,freguesiaAux,100);
	char* quanto = strdup("# Quanto?                      #\n");
	write(1,quanto,strlen(quanto));
	r4=read(0,numIncAux,100);
	char* fimMenu = strdup("#                              #\n################################\n");
	write(1,fimMenu,strlen(fimMenu));

	strncpy(distrito,distritoAux,r1-1);
	strncpy(concelho,concelhoAux,r2-1);
	strncpy(freguesia,freguesiaAux,r3-1);
	if(r3==1){
		freguesia=strdup("Default");
	}
	strncpy(numInc,numIncAux,r4-1);
	strcpy(res,"i:");
	strcat(res,distrito);
	strcat(res,":");
	strcat(res,concelho);
	strcat(res,":");
	strcat(res,freguesia);
	strcat(res,":");
	strcat(res,numInc);
	
	return res;
}

char* menuAgregar(){
	char* res = malloc(1024);
	char* s = malloc(50);
	char* distrito = malloc(50);
	char* concelho = malloc(50);
	char* freguesia = malloc(50);
	char* path = malloc(50);
	char* distritoAux = malloc(50);
	char* concelhoAux = malloc(50);
	char* freguesiaAux = malloc(50);
	char* pathAux = malloc(50);
	char* menu = strdup("################################\n#           Agregar            #\n#                              #\n# 1 - Por distrito             #\n# 2 - Por concelho             #\n# 3 - Por freguesia            #\n#                              #\n################################\n");
	int r,r2,r3,r4,r5;
	write(1,menu,strlen(menu));
	r=read(0,s,50);

	while(!((s[0]=='1') || (s[0]=='2') || (s[0]=='3'))){
		write(1,menu,strlen(menu));
		r=read(0,s,50);
	}

	strcpy(res,"a:");

	char* dist = strdup("# Distrito?                    #\n");
	char* conc = strdup("# Concelho?                    #\n");
	char* freg = strdup("# Freguesia?                   #\n");

	if(s[0]=='1'){
		strcat(res,"0:");
		write(1,dist,strlen(dist));
		r2=read(0,distritoAux,50);
		strncpy(distrito,distritoAux,r2-1);
		strcat(res,distrito);
		strcat(res,":::");
	}

	if(s[0]=='2'){
		strcat(res,"1:");
		write(1,dist,strlen(dist));
		r2=read(0,distritoAux,50);
		write(1,conc,strlen(conc));
		r3=read(0,concelhoAux,50);
		strncpy(distrito,distritoAux,r2-1);
		strncpy(concelho,concelhoAux,r3-1);
		strcat(res,distrito);
		strcat(res,":");
		strcat(res,concelho);
		strcat(res,"::");
	}

	if(s[0]=='3'){
		strcat(res,"2:");
		write(1,dist,strlen(dist));
		r2=read(0,distritoAux,50);
		write(1,conc,strlen(conc));
		r3=read(0,concelhoAux,50);
		write(1,freg,strlen(freg));
		r4=read(0,freguesiaAux,50);
		strncpy(distrito,distritoAux,r2-1);
		strncpy(concelho,concelhoAux,r3-1);
		strncpy(freguesia,freguesiaAux,r4-1);
		strcat(res,distrito);
		strcat(res,":");
		strcat(res,concelho);
		strcat(res,":");
		strcat(res,freguesia);
		strcat(res,":");
	}

	char* pathQ = strdup("Qual o nome do ficheiro com que pretende guardar?\n");
	write(1,pathQ,strlen(pathQ));
	r5=read(0,pathAux,50);
	strncpy(path,pathAux,r5-1);
	strcat(res,path);

	return res;
}

int main(int argc, char const *argv[]) {
	int pp = open("/tmp/options", O_WRONLY, 0700);
	int flag = 1;

	while(flag){
		char* res = malloc(10);
		res = menuInicio();
		//printf("%s\n",res);

		//char *aux = "2:Braga:Braga:S.Vitor"; /* Fazer Menu Para Isto */
		//char line[strlen(aux)+3];
		char* line = malloc(1024);

		if(res[0]=='1') { //incrementar
			//printf("Estou no incrementar");
			line = menuIncrementar();
			printf("%s",line);
			flag=0;
		} else 
		if(res[0]=='2'){	//agregar
			line = menuAgregar();
			printf("%s",line);
			//strcpy(line,"a:");
			//strcat(line,aux);
			flag=0;
		}

		if(!flag)
			write(pp, line, strlen(line));
	}

	return 0;
}