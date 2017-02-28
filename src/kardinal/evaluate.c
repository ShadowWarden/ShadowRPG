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


int evaluate(Input * In, Input * args, State ** Player, int *PlayerSize, VariableDec **Vars, int *size_var){
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
//	char a[20] = "Result_";
	fprintf(stderr,"Debug : Entered Evaluate\n");
	fprintf(stderr,"Debug : Printing arguments\n");
	print(*args);
	In->type = 0;
	if(EQSTR(In->name,"all")){
		fprintf(stderr,"Debug : Command is 'all'\n");
		int flag = 0;
		do{
			if(!EQSTR(args->name,"true")){
				flag++;
				fprintf(stderr,"Debug : %s is not true\n",args->name);
				strcpy(In->name,"false");
				break;
			}
			args = args->prev;
		}while(args!=NULL);
		if(flag==0){
			strcpy(In->name,"true");	
		}
		fprintf(stderr,"Debug : Flag=%d, In.name=%s\n",flag,In->name);
	}else if(EQSTR(In->name,"some")){
		fprintf(stderr,"Debug : Command is 'some'\n");
		int flag = 0;
		int lim = atoi(args->name);
		do{
			if(EQSTR(args->name,"true")){
				flag++;
				fprintf(stderr,"Debug : %s is true\n",args->name);	
			}
			args = args->prev;	
		}while(args!=NULL);
		if(flag==lim){
			strcpy(In->name,"true");	
		}else{
			strcpy(In->name,"false");		
		}
		fprintf(stderr,"Debug : Flag=%d, In.name=%s\n",flag,In->name);
	}else if(EQSTR(In->name,"not")){
/* Note to NearlyHeadless : Do an errorcheck for number of arguments here. 
*  There should be exactly 1 and no more. I'm just spitting out a warning in
*  this version of the code here :
*/
		printf("Debug : Command is 'not'\n");
		if(args->prev!=NULL){
			fprintf(stderr,"Warning : Too many arguments. The code will act only on the last argument\n");
		}
		if(EQSTR(args->name,"true")){
			fprintf(stderr,"Debug : arg=%s\n",args->name);
			strcpy(In->name,"false");
		}else if(EQSTR(args->name,"false")){
			fprintf(stderr,"Debug : arg=%s\n",args->name);
			strcpy(In->name,"true");
		}
	// Do an error check here if argument name is neither true or false
		fprintf(stderr,"Debug : Arg=%s, In.name=%s\n",args->name,In->name);
	}else if(EQSTR(In->name,"ttl")){
/* Only looking at last arg again. NearlyHeadless : Error check. In addition,
*  Replace this with binary search (O(N) vs O(log N))
*/
		int i,flag=0;
		int id = atoi(args->name);
		for(i=0;i<*PlayerSize;i++){
			printf("Debug : Player[i].id=%d\n",((*Player)+i)->id);
			if(id == ((*Player)+i)->id){
				fprintf(stderr,"Debug : State %d found at i=%d\n",id,i);
				strcpy(In->name,"true");			
				flag++;
				break;
			}
		}
		if(flag == 0){
			fprintf(stderr,"Debug : State %d not found\n",id);
			strcpy(In->name,"false");			
		}
	}else if(EQSTR(In->name,"addttl")){
/* Again. This only accepts exactly one argument. Error checks
*/
		add_state_to_player(atoi(args->name),Player,PlayerSize);
		fprintf(stderr,"Debug : State %s added to player\n",Titles[atoi(args->name)-1].name);
		strcpy(In->name,"true");			
	}else if(EQSTR(In->name,"rmttl")){
/* Remove title by ID from the player's stack
*/
		int result;
		result = remove_state_from_player(atoi(args->name),Player,PlayerSize);
		if(result){
			strcpy(In->name,"true");
		}else{
			strcpy(In->name,"false");
		}
	}else if(EQSTR(In->name, "setvar")){
		int result = -setvar(Vars,size_var,&args);
		if(result != 0){
			fprintf(stderr,"Error : Setvar failed with error code %d. Look at the documentation to troubleshoot\n",result);
			strcpy(In->name,"false");
		}else{
			strcpy(In->name,"true");
		}
		args=args->prev;
	}else{
/* Come up with a better default condition
*/
		strcpy(In->name,"false");
	}
		
	printf("Debug : Leaving Evaluate\n");
	return 0;
}
