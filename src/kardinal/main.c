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
#include "/home/omkar/programs/gdb-7.2/readline/readline.h"
#include "kardinal.h"

#define MAX_INPUT 256

int TitleSize;
State * Titles;

int main(int argc, char ** argv){
		/* Declarations */
		char * line = (char *) NULL;
		State *Player;
		int PlayerSize = 0;
		int if_false_flag = 0;
		int line_number=0;
		int scope_level = 0;
		int debug = 0;

//		if(argc<3){
//				printf("2 input parameters needed!\n");
//				exit(1);
//		}
		FILE * state_in = fopen(argv[2],"r");
			 //  * fin = fopen(argv[1],"r");
			 /*	int debug=0;
				if(argc>3){
				if(strcmp(argv[3],"--debug")==0){
				printf("Yay\n");
				debug=1;
				}
				else{
				printf("Unidentifiable argument %s\n", argv[3]);
				exit(2);
				}
				}
			  */
			 // Initialize variable stack
		SymTable * S = (SymTable *) malloc (sizeof(SymTable));

//		build_states_test(state_in, debug);
		//	dump_states_test(debug);
//		add_state_to_player(2,&Player,&PlayerSize);
//		printf("Debug : %d %s %d\n",Player[0].id,Player[0].name,Player[0].attribute);
//		fclose(state_in);

		//		line = readline(">")
		do{
				//	In->prev = NULL;
				if(line){
					free(line);
					line = (char *) NULL;		
				}
				line = readline("Kardinal > ");
				int i=0;
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
				In = build(In,line);
				//		printf("%s : %d : %d : %s\n\n\n",In->name,In->lvl,In->type,In->prev->name);


				int res = parse(&In,&Player,&PlayerSize,S,line_number,debug);

				if(res == 201){
						if_false_flag = 1;
				}else if(res == -202){
						/* Endif. Get rid of local symbol table */	
						if(!if_false_flag && scope_level != 0){
								if(S->level == scope_level){
										SymTable *tmp = S;
										S = S->prev;
										Free_var(*tmp);
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
				}else if(res!=1 && res){
						/* There was an error. Exit */
						Free(In);
						Free_var(*S);
						free(S);
						free(Titles);
						return -1;

				}
				(debug == 1) ? printf("Debug : Command stack after parse\n") : 0;
				print(*In,debug);
				(debug==1) ? printf("\nDebug : Final Result\n") : 0;
				print_final(*In, debug);
				//	scanf("%c",&junk);	
				(debug==1) ? printf("\nDebug : Size of Player state stack : %d\n",PlayerSize) : 0;
				print_player_state(Player,PlayerSize,debug);
				Free(In);
		}while(line != NULL);
	
		//	print_variable_stack(S);
		(debug==1) ? printf("Debug : Survived print_variable_stack\n") : 0;
		Free_var(*S);
		free(S);
		(debug==1) ? printf("Debug : Survived Free_var\n") : 0;
		free(Titles);
		//	free(Player);
		return 0;
}
