/* kardinal/evaluate.c
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
#include <stdlib.h>
#include <string.h>
#include "kardinal.h"

#define EQSTR(a,b) (strcmp(a,b)==0)

int evaluate(Input * In, Input * args, State ** Player, int *PlayerSize){
/* Dummy evaluate function. Must be updated in the next few iterations. 
* Perhaps a starting project for NearlyHeadless?
* At present, it does 'all' (universal and), 'one' (exactly one true) and 'not' 
* - seems to work fine, although we need to come up with test cases that
* account for all possible corner cases. See debug.txt
* -- OHR
*/
	char a[20] = "Result_";
	printf("Debug : Entered Evaluate\n");
	printf("Debug : Printing arguments\n");
	print(*args);
	In->type = 0;
	if(EQSTR(In->name,"all")){
		printf("Debug : Command is 'all'\n");
		int flag = 0;
		do{
			if(!EQSTR(args->name,"true")){
				flag++;
				printf("Debug : %s is not true\n",args->name);
				strcpy(In->name,"false");
				break;
			}
			args = args->prev;
		}while(args!=NULL);
		if(flag==0){
			strcpy(In->name,"true");	
		}
		printf("Debug : Flag=%d, In.name=%s\n",flag,In->name);
	}else if(EQSTR(In->name,"one")){
		printf("Debug : Command is 'one'\n");
		int flag = 0;
		do{
			if(EQSTR(args->name,"true")){
				flag++;
				printf("Debug : %s is true\n",args->name);	
			}
			args = args->prev;	
		}while(args!=NULL);
		if(flag==1){
			strcpy(In->name,"true");	
		}else{
			strcpy(In->name,"false");		
		}
		printf("Debug : Flag=%d, In.name=%s\n",flag,In->name);
	}else if(EQSTR(In->name,"not")){
/* Note to NearlyHeadless : Do an errorcheck for number of arguments here. 
*  There should be exactly 1 and no more. I'm just spitting out a warning in
*  this version of the code here :
*/
		printf("Debug : Command is 'not'\n");
		if(args->prev!=NULL){
			printf("Warning : Too many arguments. The code will act only on the last argument\n");
		}
		if(EQSTR(args->name,"true")){
			printf("Debug : arg=%s\n",args->name);
			strcpy(In->name,"false");
		}else if(EQSTR(args->name,"false")){
			printf("Debug : arg=%s\n",args->name);
			strcpy(In->name,"true");
		}
	// Do an error check here if argument name is neither true or false
		printf("Debug : Arg=%s, In.name=%s\n",args->name,In->name);
	}else if(EQSTR(In->name,"ttl")){
/* Only looking at last arg again. NearlyHeadless : Error check. In addition,
*  Replace this with binary search (O(N) vs O(log N))
*/
		int i,flag=0;
		int id = atoi(args->name);
		for(i=0;i<*PlayerSize;i++){
			printf("Debug : Player[i].id=%d\n",((*Player)+i)->id);
			if(id == ((*Player)+i)->id){
				printf("Debug : State %d found at i=%d\n",id,i);
				strcpy(In->name,"true");			
				flag++;
				break;
			}
		}
		if(flag == 0){
			printf("Debug : State %d not found\n",id);
			strcpy(In->name,"false");			
		}
	}else if(EQSTR(In->name,"addttl")){
/* Again. This only accepts exactly one argument. Error checks
*/
		int i;
		add_state_to_player(atoi(args->name),Player,PlayerSize);
		printf("Debug : State %s added to player\n",Titles[atoi(args->name)-1].name);
		strcpy(In->name,"true");			
	}
	printf("Debug : Leaving Evaluate\n");
	return 0;
} 