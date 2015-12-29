/* read.c
*  Omkar H. Ramachandran
*
*  Just reading in the convo stuff. Prototype. Finalize Kardinal before adding 
*  to the engine.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLN 100
#define MAXTG 20
#define MAXVAR 20

int main(int argc, char ** argv){
	char file[]="char-1002.cn";
	FILE *fp = fopen(file,"r");
	char tag[MAXTG]="";
	int i;
	char junk;	

	fseek(fp,SEEK_SET,0);
	fscanf(fp,"%s\n",tag);
	while(strcmp(tag,"END")!=0){
		char var[MAXVAR]="";
		while(strcmp(var,"End:")!=0){
			char line[MAXLN]="";
			char esc = fgetc(fp);
			i=0;
			while(esc!=':'){
				var[i] = esc;
				i++;
				esc = fgetc(fp);
			}
			var[i] = ':';
			var[i+1] = '\0';
//			printf("%s\n",var);
			i=0;
			do{
				esc = fgetc(fp);
			}while(esc == ' ');

			while(esc!='\n'){
				if(i<MAXLN-1){
					line[i] = esc;
					i++;
				}
				esc = fgetc(fp);
			}
			line[i] = '\0';
			if(strcmp(var,"Say:")==0 || (var[0]=='R' && var[1]=='s' && var[2]=='p')){
				if( (int)(var[3]-'0') < 10) // 9 Responses per Say
					printf("%d: %s\n",(int)(var[3]-'0'),line);
				else
					printf("%s\n",line);
			}
//			printf("\n");
		}
//		printf("\n");
		fscanf(fp,"%s\n",tag);
	}
}
