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

int TitleSize;
State * Titles;

int main(int argc, char ** argv){
	/* Declarations */
	char line[MAX_INPUT];
//	char ** result;
//	char input[MAX_INPUT];
	int Fsize;
	State *Player;
	int PlayerSize = 0;
	
	if(argc<3){
		printf("2 input parameters needed!\n");
		exit(1);
	}
	FILE * state_in = fopen(argv[2],"r"),
	     * fin = fopen(argv[1],"r");
	Fsize = getsize(fin);

	int debug=0;
	if(argc>3){
		if(strcmp(argv[3],"--debug")){
			debug=1;
		}
	}
	// Initialize variable stack
	VariableDec * Vars;
	int size_var = 0;
	
	build_states_test(state_in, debug);
	dump_states_test(debug);
//	add_state_to_player(2,&Player,&PlayerSize);
//	printf("Debug : %d %s %d\n",Player[0].id,Player[0].name,Player[0].attribute);
	while(fgets(line,MAX_INPUT,fin)){
	//	In->prev = NULL;
		int i=0,err,maxlvl;
		char ch=line[i];
/* Pretty sure my beautiful conditional operator is no longer necessary
*  :'-( - OHR
*/
//		int size_in = (MAX_INPUT>(sizeof(line)))?MAX_INPUT:sizeof(line);
		while(ch==' '){
			i++;
			ch = line[i];
		}
		(debug==1) ? printf("Debug : ch = %c\n",ch) : 0;
		if(ch == '#'){
		// Comment
			continue;
		}		
		(debug==1) ? printf("Debug : Command = %s\n",line) : 0;
		// Build the command stack
		Input *In = (Input *) malloc (sizeof(Input));
		In = build(In,line);
	//	printf("%s : %d : %d : %s\n\n\n",In->name,In->lvl,In->type,In->prev->name);
		In = parse(In,&Player,&PlayerSize,&Vars,&size_var,debug);
		(debug == 1) ? printf("Debug : Command stack after parse\n") : 0;
		print(*In);
		(debug==1) ? printf("\nDebug : Final Result\n") : 0;
		print_final(*In);
	//	scanf("%c",&junk);	
		(debug==1) ? printf("\nDebug : Size of Player state stack : %d\n",PlayerSize) : 0;
		print_player_state(Player,PlayerSize,debug);
		Free(In);
	}	
	if(size_var!=0){
		print_variable_stack(*Vars, debug);
		(debug==1) ? printf("Debug : Survived print_variable_stack\n") : 0;
		Free_var(Vars);
	}
	(debug==1) ? printf("Debug : Survived Free_var\n") : 0;
	free(Titles);
	free(Player);
	fclose(state_in);
	return 0;
}
