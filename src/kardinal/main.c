/* kardinal/main.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  Main script parser/logic interface of the game. Do not edit this file unless 
*  absolutely necessary
* 
*
*  This project is under the GNU General GPL version 3.0 license. For more 
*  information about the license, refer the LICENCE file in the root directory 
*  or go online to <http://www.gnu.org/licenses>
*  
*  Any redistribution of this code must contain this header in its entirety
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "kardinal.h"

#define MAX_INPUT 256

//int TitleSize;
//State * Titles;

int main(int argc, char ** argv){
	/* Declarations */
	char line[MAX_INPUT];
//	State *Player;
//	int PlayerSize = 0;
	int if_false_flag = 0;
	int line_number=0;
	int scope_level = 0;

	if(argc<2){
		printf("Input file needed!\n");
		exit(1);
	}
	int debug=0;
	if(strcmp(argv[1],"--version")==0){
		banner();
		return 0;
	}
	if(argc>2){
		if(strcmp(argv[2],"--debug")==0){
			printf("Yay\n");
			debug=1;
		}
		else{
			printf("Unidentifiable argument %s\n", argv[2]);
			exit(2);
		}
	}
	
	FILE * fin;
   	if(!(fin = fopen(argv[1],"r"))){
		fprintf(stderr,"File %s does not exist\n",argv[1]);
		return 1;
	}
	// Initialize variable stack
	SymTable * S = (SymTable *) malloc (sizeof(SymTable));

	int i;
	for(i=0;i<CAP;i++)
		S->Vars[i] = NULL;
   	S->level = 0;
	S->prev = NULL;   

//	dump_states_test(debug);
//	add_state_to_player(2,&Player,&PlayerSize);
//	printf("Debug : %d %s %d\n",Player[0].id,Player[0].name,Player[0].attribute);
	while(fgets(line,MAX_INPUT,fin)){
	//	In->prev = NULL;
		int i=0, res;
		int num_temp_variables = 0;
		char ch=line[i];
		line_number++;	
/* Pretty sure my beautiful conditional operator is no longer necessary
*  :'-( - OHR
*/
//		int size_in = (MAX_INPUT>(sizeof(line)))?MAX_INPUT:sizeof(line);
		while(ch==' ' || ch=='\t'){
			i++;
			ch = line[i];
		}
		(debug==1) ? printf("Debug : ch = %c\n",ch) : 0;
		if(ch == '#' || (if_false_flag==1 && ch!='e')){
		// Comment and not endif!
			continue;
		}
		(debug==1) ? printf("Debug : Command = %s\n",line) : 0;
		// Build the command stack
		Input *In = (Input *) malloc (sizeof(Input));
		In->name[0] = '\0';
		In->type = 0;
		In->lvl = 0;
		In->prev = NULL;
		res = build(&In,line);
//		printf("%s : %d : %d : %s\n\n\n",In->name,In->lvl,In->type,In->prev->name);	
		res = parse(&In,&S,line_number,&num_temp_variables,debug);
		
		if(res == 201){
			if_false_flag = 1;
		}else if(res == -202){
			/* Endif. Get rid of local symbol table */	
			if(!if_false_flag && scope_level != 0){
				if(S->level == scope_level){
					SymTable *tmp = S;
					S = S->prev;
					Free_var(tmp);
					free(tmp);
				}
				scope_level -= 1;
			}
			if_false_flag = 0;
		}else if(res == 202){
			/* If statement. Create local symtable */
			SymTable * tmp = S;
			scope_level += 1;
			S = (SymTable *) malloc (sizeof(SymTable));
			S->level = scope_level;
			S->prev = tmp;
			for(i=0;i<CAP;i++)
				S->Vars[i] = NULL; 
		}else if(res!=1 && res){
		/* There was an error. Exit */
			Free(In);
			Free_var(S);
			free(S);
			fclose(fin);
			return -1;
		
		}
		
		(debug == 1) ? printf("Debug : Command stack after parse\n") : 0;
		print(*In,debug);
		(debug==1) ? printf("\nDebug : Final Result\n") : 0;
		print_final(*In, debug);
	//	scanf("%c",&junk);	
		Free(In);
	//	print_variable_stack(*S);
	}	
//	print_variable_stack(*S);
	(debug==1) ? printf("Debug : Survived print_variable_stack\n") : 0;
	fclose(fin);
	Free_var(S);
	free(S);
	return 0;
}
