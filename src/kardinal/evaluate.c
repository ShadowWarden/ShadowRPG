/* kardinal/evaluate.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  Vishnu Sharma
*  vishnu.rk1995@gmail.com
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

int evaluate(Input * In, Input * args, State ** Player, int *PlayerSize, VariableDec* Vars){
/* At present, it works. We have a few different thigns that evaluate can do. The three things I
*  want done ASAP are error checks (NearlyHeadless, all yours), variable support and condensing
*  the code so that this function looks like 
*  if(EQSTR(In->name,<command>)){
*	<initialization of appropriate variables>  
*	<command>(<args>);
*  }
*/
//	char a[20] = "Result_";
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
	}else if(EQSTR(In->name,"some")){
		printf("Debug : Command is 'some'\n");
		int flag = 0;
		int lim = atoi(args->name);
		do{
			if(EQSTR(args->name,"true")){
				flag++;
				printf("Debug : %s is true\n",args->name);	
			}
			args = args->prev;	
		}while(args!=NULL);
		if(flag==lim){
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
		add_state_to_player(atoi(args->name),Player,PlayerSize);
		printf("Debug : State %s added to player\n",Titles[atoi(args->name)-1].name);
		strcpy(In->name,"true");			
	}
/** This will define and set variables. Once this is done, we essentially have a programming language  
*  Ofc, we need to define loops and conditionals, but otherwise, we've got it all
*  setvar(varname,type,value)
*
		*VarSize+=1;
		if(*VarSize > 1)
			*Vars = realloc(*Vars,(*VarSize)*sizeof(Var));
		else
			*Vars = (Var *) malloc (sizeof(Var));
		Input * tmp1=args->prev;  // Holds 'type'
		Input * tmp2=tmp1->prev;  // Holds 'varname'
		char * value = args->name;
		char * name = tmp2->name;
		char * type = tmp1->name;
// I'm setting size to 1 for now. We'll deal with arrays later, if needed
		(*Var)[VarSize-1].size = 1;
		if(EQSTR(type,"int")){
// Ugh.. Too many pointers. Can't think of an easier way to do this though
			(*Vars)[i].att = (int *) malloc ((*Vars)[VarSize-1].size*sizeof(int));
			*((*Vars)[i].att) = atoi(value);
			

	}
*/
	else if(EQSTR(In->name, "setvar")){
		VariableDec *var = (VariableDec*)malloc(sizeof(VariableDec));
		Vars->selfpointer=Vars;
		var->prev=Vars->selfpointer;
		var->selfpointer=NULL;
		Vars=var;
		strcpy(var->varname,args->name);
		args=args->prev;
		strcpy(var->type,args->name);
		args=args->prev;
		if (strcmp(var->type, "string")==0||strcmp(var->type,"int")||strcmp(var->type,"double")){
			var->varname=(char*)malloc(sizeof(char)*strlen(var->varname));
			var->size=strlen(var->varname);
			strcpy(var->addrs,args->name);
		}
		else {	
			printf("Error:Primitive Data Type doesn't exist!");
			return NULL;
		}
	}
	printf("Debug : Leaving Evaluate\n");
	return 0;
}
