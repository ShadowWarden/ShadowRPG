/* kardinal/general.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  Vishnu Sharma
*  vishnu.rk1995@gmail.com
*
*  General functions (print, if - perhaps basic math functions like add)
*  should be defined here
*
*  This project is under the GNU General GPL version 3.0 license. For more 
*  information about the license, refer the LICENCE file in the root directory 
*  or go online to <http://www.gnu.org/licenses>
*  
*  Any redistribution of this code must contain this header in its entirety
*/

#include<stdio.h>
#include"kardinal.h"
#include<stdlib.h>
#include<string.h>

#define EQSTR(a,b) (strcmp(a,b)==0)

int Print(Input * args, SymTable S, int debug){
	/* Change print so that it does pattern matching.
	 * The final syntax should look as follows:
	 * Print("Value of A is ",A,"\n")
	 */
	VariableDec * Vars = NULL;	
	while(args!=NULL){
		VariableDec *tmp = Vars; 
		if(args->name[0]=='"'){
			Vars = (VariableDec *) malloc (sizeof(VariableDec)); 
			Vars->value = (char *) malloc (sizeof(char)*(strlen(args->name)-2));
			int i;
			for(i=1;i<strlen(args->name)-1;i++){
				if(args->name[i]=='\\'){
					Vars->value[i-1]='\n';
					i++;
				}else
					Vars->value[i-1]=args->name[i];
			}
			Vars->value[i-1]='\0';
			strcpy(Vars->type,"string");			
		}else{
			VariableDec *Found = find_in_hash(S,args->name);
			Vars = (VariableDec *) malloc (sizeof(VariableDec)); 
			Vars->value = (int *) malloc (sizeof(int));
			*(Vars->value) = *(Found->value);
			strcpy(Vars->type,"int");
		}
		Vars->prev = tmp;
		args = args->prev;
	}
	while(Vars != NULL){
		if(strcmp(Vars->type,"int") == 0){
			printf("%d",*(Vars->value));
		}else{
			printf("%s",(Vars->value));
		}
		VariableDec *tmp = Vars;
		Vars = Vars->prev;
		free(tmp->value);
		free(tmp);
	}
	return 0;
}


