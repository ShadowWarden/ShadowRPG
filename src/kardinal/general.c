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

#include"kardinal.h"

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
			Vars->value = (char *) malloc (sizeof(char)*(strlen(args->name)-1));
			int i;
			int flag = 0;
			char * array = (char *) Vars->value;
			for(i=1;i<strlen(args->name)-1;i++){
				if(args->name[i]=='\\'){
					array[i-1-flag]='\n';
					i++;
					flag++;
				}else
					array[i-1-flag]=args->name[i];
			}
			array[i-1-flag]='\0';
			Vars->type = 's';			
		}else{
			VariableDec *Found;
			int res = find_in_hash(&Found,S,args->name);
			if(res != 0){
			/* Undeclared variable */
					return res;
			}
			Vars = (VariableDec *) malloc (sizeof(VariableDec)); 
			if(Found->type == 'i'){
				Vars->value = (int *) malloc (sizeof(int));
				*((int *)Vars->value) = *((int *)Found->value);
				Vars->type = 'i';
			}else if(Found->type == 's'){
				Vars->value = (char *) malloc (sizeof(char)*(strlen(Found->value)+1));
				strcpy((char *)Vars->value,(char *)Found->value);
	//			fprintf(stderr,"Debug: Vars: %s\n",Vars->value);
				Vars->type = 's';
			
			}
		}
		Vars->prev = tmp;
		args = args->prev;
	}
	while(Vars != NULL){
		if(Vars->type == 'i'){
			printf("%d",*((int *)Vars->value));
		}else{
			printf("%s",(char *)(Vars->value));
		}
		VariableDec *tmp = Vars;
		Vars = Vars->prev;
		free(tmp->value);
		free(tmp);
	}
	printf("\n");
	return 0;
}

int If(Input * args,int debug){
	if(strcmp(args->name,"true")==0){
		return 0;
	}else if(strcmp(args->name,"false")==0){
		return -1;
	}else{
		/* Invalid input */
		return -2;
	}
}


