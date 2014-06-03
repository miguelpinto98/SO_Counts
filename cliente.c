#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* menuInicio(){
	char* s = malloc(50);
	char* menu = strdup("###################################\n#                                 #\n# 1 - Incrementar                 #\n# 2 - Agregar                     #\n# 0 - Sair                        #\n#                                 #\n###################################\n");
	int r;
	write(1,menu,strlen(menu));
	r=read(0,s,50);

	if(!((s[0]=='1' && strlen(s)==2) || (s[0]=='2' && strlen(s)==2) || (s[0]=='0' && strlen(s)==2)))
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
	char* menu = strdup("	################################\n#         Incrementar          #\n#                              #\n# Em que distrito?             #\n");
	write(1,menu,strlen(menu));
	r1=read(0,distritoAux,100);
	//printf("%s\n", distritoAux);
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
	strcat(res,numInc);
	strcat(res,":");
	strcat(res,distrito);
	strcat(res,":");
	strcat(res,concelho);
	strcat(res,":");
	strcat(res,freguesia);	
	
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
	char* menu = strdup("#######################################################\n#                        Agregar                      #\n#                                                     #\n# Quantos prefixos pretende inserir (1,2 ou 3):       #\n#                                                     #\n#######################################################\n");
	int r,r2,r3,r4,r5,r6,r7;
	write(1,menu,strlen(menu));
	r=read(0,s,50);

	while(!((s[0]=='1') || (s[0]=='2') || (s[0]=='3'))){
		write(1,menu,strlen(menu));
		r=read(0,s,50);
	}

	strcpy(res,"a:");
	char* s1 = malloc(10);
	char* s2 = malloc(10);
	char* dist = strdup("# Distrito?                    #\n");
	char* conc = strdup("# Concelho?                    #\n");
	char* freg = strdup("# Freguesia?                   #\n");
	char* nivel012 = strdup("#######################################################\n#                                                     #\n# Qual o nível?                                       #\n#                                                     #\n# 0 - Por distrito                                    #\n# 1 - Por concelhos                                   #\n# 2 - Por freguesias                                  #\n#                                                     #\n#######################################################\n");
	char* nivel01 = strdup("#######################################################\n#                                                     #\n# Qual o nível?                                       #\n#                                                     #\n# 0 - Por concelho                                    #\n# 1 - Por freguesias                                  #\n#                                                     #\n#######################################################\n");

	if(s[0]=='1'){
		
		write(1,dist,strlen(dist));
		r2=read(0,distritoAux,50);
		strncpy(distrito,distritoAux,r2-1);
		write(1,nivel012,strlen(nivel012));
		r6=read(0,s2,50);
		strncpy(s1,s2,r6-1);
		strcat(res,s1);
		strcat(res,":");
		strcat(res,distrito);
		strcat(res,":::");
	}

	if(s[0]=='2'){
		write(1,dist,strlen(dist));
		r2=read(0,distritoAux,50);
		write(1,conc,strlen(conc));
		r3=read(0,concelhoAux,50);
		strncpy(distrito,distritoAux,r2-1);
		strncpy(concelho,concelhoAux,r3-1);
		write(1,nivel01,strlen(nivel01));
		r6=read(0,s2,50);
		strncpy(s1,s2,r6-1);
		strcat(res,s1);
		strcat(res,":");
		strcat(res,distrito);
		strcat(res,":");
		strcat(res,concelho);
		strcat(res,"::");
		printf("%s",res);
	}

	if(s[0]=='3'){
		write(1,dist,strlen(dist));
		r2=read(0,distritoAux,50);
		write(1,conc,strlen(conc));
		r3=read(0,concelhoAux,50);
		write(1,freg,strlen(freg));
		r4=read(0,freguesiaAux,50);
		strncpy(distrito,distritoAux,r2-1);
		strncpy(concelho,concelhoAux,r3-1);
		strncpy(freguesia,freguesiaAux,r4-1);
		strcat(res,"2:");
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

void handler() {
}

int main(int argc, char const *argv[]) {
	
	signal(SIGALRM,handler);

	int flag = 1, pid;

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
			//printf("%s",line);
			flag=0;
		} else 
		if(res[0]=='2'){	//agregar
			line = menuAgregar();
			//printf("%s",line);
			//strcpy(line,"a:");
			//strcat(line,aux);
			pid = getpid();

			char auxpid[15];
			sprintf(auxpid,":%d",pid);
			strcat(line,auxpid);

			flag=0;
		}
		else
		if(res[0]=='0'){
			exit(0);
		}


		if(!flag) {
			int pp = open("/tmp/options", O_WRONLY, 0700);
			write(pp, line, strlen(line));
			close(pp);
			
			if(res[0]=='2')
				pause();
		}
	}

	return 0;
}