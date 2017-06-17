/* kardinal/evaluate.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  Vishnu Sharma
*  vishnu.rk1995@gmail.com
*
*  Main script parser/logic interface of the game. All available script
*  functions should be defined here in if statements
*
*  This project is under the GNU General GPL version 3.0 license. For more 
*  information about the license, refer the LICENCE file in the root directory 
*  or go online to <http://www.gnu.org/licenses>
*  
*  Any redistribution of this code must contain this header in its entirety
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kardinal.h"

#define EQSTR(a,b) (strcmp(a,b)==0)


int evaluate(Input * In, Input * args, State ** Player, int *PlayerSize, VariableDec **Vars, int *size_var, int debug){
/* At present, it works. We have a few different things that evaluate can do. The three things I
*  want done ASAP are error checks (NearlyHeadless, all yours), variable support and condensing
*  the code so that this function looks like 
*  if(EQSTR(In->name,<command>)){
*	<initialization of appropriate variables>  
*	<command>(<args>);
*  }
*  If NearlyHeadless understands the code by the end of the week, then this should really be something
*  that he should do. I'll do it otherwise - but right now, I'm only thinking about variable support
*  -- OHR
*/
	(debug==1) ? fprintf(stderr,"Debug : Entered Evaluate\n") : 0;
	(debug==1) ? fprintf(stderr,"Debug : Printing arguments\n") : 0;
//	print(*args);
	In->type = 0;
	if(EQSTR(In->name,"all")){
		All(In,args,debug);
	}else if(EQSTR(In->name,"some")){
		Some(In,args,debug);
	}else if(EQSTR(In->name,"not")){
/* Note to NearlyHeadless : Do an errorcheck for number of arguments here. 
*  There should be exactly 1 and no more. I'm just spitting out a warning in
*  this version of the code here :
*/
		Not(In,args,debug);
	}else if(EQSTR(In->name,"ttl")){
/* Only looking at last arg again. NearlyHeadless : Error check. In addition,
*  Replace this with binary search (O(N) vs O(log N))
*/
		int id = atoi(args->name);
		int result = -find_ttl(id,Player,PlayerSize,debug);
		if(result){
			strcpy(In->name,"false");			
		}else{
			strcpy(In->name,"true");	
		}
	}else if(EQSTR(In->name,"addttl")){
/* Again. This only accepts exactly one argument. Error checks
*/
		add_state_to_player(atoi(args->name),Player,PlayerSize);
		(debug==1) ? fprintf(stderr,"(addttl) Debug : State %s added to player\n",Titles[atoi(args->name)-1].name) : 0;
		strcpy(In->name,"true");			
	}else if(EQSTR(In->name,"rmttl")){
/* Remove title by ID from the player's stack
*/
		int result;
		result = remove_state_from_player(atoi(args->name),Player,PlayerSize,debug);
		if(result){
			strcpy(In->name,"true");
		}else{
			strcpy(In->name,"false");
		}
	}else if(EQSTR(In->name, "setvar")){
		int result = -setvar(Vars,size_var,&args,debug);
		if(result != 0){
			(debug==1) ? fprintf(stderr,"(setvar) Error : Setvar failed with error code %d. Look at the documentation to troubleshoot\n",-result) : 0;
			strcpy(In->name,"false");
		}else{
			strcpy(In->name,"true");
		}
		args=args->prev;
	}else if(EQSTR(In->name, "EQ")){
		VariableDec * Var1 = *Vars;
		VariableDec * Var2 = Var1->prev;
		int res = EQ(Var1,Var2,debug);
		if(res == 0)
			strcpy(In->name,"true");
		else
			strcpy(In->name,"false");
		/* Need to do an error condition here */
	}else if(EQSTR(In->name, "GE")){
		VariableDec * Var1 = *Vars;
		VariableDec * Var2 = Var1->prev;
	
		int res = GE(Var1,Var2,debug);
		if(res == 0)
			strcpy(In->name,"true");
		else
			strcpy(In->name,"false");
		/* Need to do an error condition here */

	}else if(EQSTR(In->name, "LE")){
		VariableDec * Var1 = *Vars;
		VariableDec * Var2 = Var1->prev;
	
		int res = LE(Var1,Var2,debug);
		if(res == 0)
			strcpy(In->name,"true");
		else
			strcpy(In->name,"false");
		/* Need to do an error condition here */
	}else{
/* Come up with a better default condition
*/
		strcpy(In->name,"false");
	}
		
	(debug==1) ? printf("Debug : Leaving Evaluate\n") : 0;
	return 0;
}
