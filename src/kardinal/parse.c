/* kardinal/parse.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  Main script parser/logic interface of the game. The main parsing functions 
*  are declared here. Do not edit this file unless absolutely necessary
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

#define MAXBUF 100

void Debug(char * msg){
	fprintf(stderr,"%s",msg);
}

int freeform_new(Input **In, Input cur, int pos){
	// Creates a new node in the freeform stack

	Input * new = (Input *) malloc (sizeof(Input));
	new->lvl = cur.lvl;
	new->type = cur.type;
	strcpy(new->name,cur.name);
	new->prev = *In;
//	new->pos = pos;
	*In = new;
//	printf("Debug : %d : %s : %d : %d\n",cur.lvl,cur.name,cur.type,pos);	
	return 0;
}

Input * build(Input * In, char *in){
/* This takes the input string - something like all(ttl(abc,def,efg)) and breaks
*  it up as follows : 
*  1. Anything that preceeds a bracket is a command. In this case, that refers
*     to all and tll (Node.type=1)
*  2. Everything else is a argument (Node.type=0)
*  In addition to this, it assigns levels as shown below :
*  Cmd : all(ttl(abc,def))
*  Lvl :  0   1   2   2
*/
	// Declarations
	char buf[MAXBUF];
	int i = 0;
	int index = 0;
	int lvl = 0;
	int maxlvl = 0;
	int flag_space = 0;
	char ch = in[i];	
	// Remove preceding spaces
	while(ch == ' '){
		i++;
		ch = in[i];
	}
//	Debug(debug,"Debug : Removed Spaces\n");
	int flag = 0;
	while(i<strlen(in)){
		ch = in[i];
//		Input * cmd;
		if(ch == '('){
/* If the buffer character is a (, then the word that came before it has 
*  to be a command (Rule 1). Hence, we give it type 1. We check for 
*  flag==0 so that we can assign Node->prev to NULL (this is a bit clunky
*  needs to be improved)
*/			
			buf[index] = '\0';
			if(flag==0){
				strcpy(In->name,buf);
				In->type = 1;
				In->prev = NULL;
				In->lvl = lvl;
			}else{
				Input * new = (Input *) malloc (sizeof(Input));
				strcpy(new->name,buf);
				new->type = 1;				
				new->prev = In;
				new->lvl = lvl;
				In = new;
			}
			flag ++;
			index = 0;
			lvl+=1;
		}else if(ch == ',' || (ch == ')' && index!=0)){
/* If the buffer character is a ',' or a ')', then the word that came 
*  before it has to be an argument. The if statements below are to avoid 
*  corner cases that occur when you have a ) followed by a , and when you're
*  looking at the final ) 
*/
			buf[index] = '\0';
		//	printf("buf : %s\n",buf);
			Input * new = (Input *) malloc (sizeof(Input));
			strcpy(new->name,buf);
			new->type = 0;
			new->lvl = lvl;
			maxlvl = (lvl>maxlvl)?lvl:maxlvl;
			new->prev = In;
	//		new->parent = In;
			In = new;
			flag++;
			index = 0;
			if(ch == ')' && i != strlen(in)-1){
	// Skip the next 'comma' Ex : var(var2(arg1,arg2),arg3) Skip the comma after arg2) and go straight to arg3
				lvl -= 1;
				i++;
				ch = in[i];
				while(ch == ' ' || ch == ','){
					i++;
					ch = in[i];
				}
				continue;
			} 
		}else if(ch != ' ' && index < MAXBUF && ch!=')'){
/* If the character looked at is neither a ',' nor a bracket, then it must
*  be a word (either arg or cmd). Write to buffer.
*/
			if(ch == '"'){
				flag_space = (flag_space == 1)? 0 : 1;
			}
			buf[index] = ch;
			index++;
		//	printf("buf : %s\n",buf);
		}
		if(flag_space && ch == ' '){
			buf[index] = ch;
			index++;
		}
		i++;
	}
//	printf("%s : %d : %d : %s\n\n\n",In->name,In->lvl,In->type,In->prev->name);
	return In;	
}

void Free(Input * In){
	while(In != NULL){
		Input * tmp = In;
		In = In->prev;
		free(tmp);
	}
	free(In);
}



void print(Input In, int debug){
	Input *tmp = &In;
//	printf("%d\n",strcmp(In.name,"def\0"));
	int flag = 0;
//	printf("i : str : t : l\n");
//	printf("Debug : tmp = %p\n",tmp);
	while(tmp != NULL){
	//	char buf[20];
		(debug==1) ? fprintf(stderr,"Debug : %d : %s : %d : %d\n",flag,tmp->name,tmp->type,tmp->lvl) : 0;
	//	debug(debug)
		tmp = tmp->prev;
		flag++;
	}
}

void print_final(Input In, int debug){
	Input *tmp = &In;
	int flag = 0;
	while(tmp != NULL){
		if(tmp->prev==NULL){
			(debug==1) ? fprintf(stderr,"Debug : %d : %s : %d : %d\n",flag,tmp->name,tmp->type,tmp->lvl) : 0;
		}
		flag++;
		tmp=tmp->prev;
	}
}

Input * selective_free(Input *In, int lvl_limit){
	Input *cur = In;
	Input *old = NULL;
	while(cur!=NULL){
		if(cur->lvl == lvl_limit){
			Input * tmp = cur;
			cur = cur->prev;
			if(old!=NULL)
				old->prev = cur;
			else
				In = cur;
			free(tmp);
		}else{
			Input *tmp = cur;
			cur = cur->prev;
			old = tmp;
		}
	}
	return In;
}

int write(Input *In1, Input *In2){
	strcpy(In1->name,In2->name);
	In1->type = In2->type;
	In1->lvl = In2->lvl;
	In1->prev = In2->prev;
	return 0;
}

void sequential_print(Input *In, char *name, int debug){
	int i=0;
	Input *tmp = In;
	do{
		(debug==1) ? fprintf(stderr,"Debug : %s[%d].name = %s\n",name,i,tmp->name) : 0;
		tmp = tmp->prev;
		i++;
	}while(tmp!=NULL);
}

Input * parse(Input *In, State **Player, int *PlayerSize, SymTable *S, int debug){
	int pos = 0;	
	Input *argsold = NULL;
	Input *old = In;
	Input *cur = In->prev;
	int curlvl = old->lvl; 
// I'm shifting the defn of curlvl here to make things a little clearer.

	(debug==1) ? fprintf(stderr,"Debug : Entered parse\n") : 0;

	while(cur!=NULL){
		if(cur->lvl > curlvl){
/* If stmt 1 in the gameplan. If cur->lvl > curlvl, then we are inside another
* command. Something like ..cur),old.. As a result, we need to add old to 
* argsold and we should be done.
*/
			(debug==1) ? fprintf(stderr,"Debug : Entered if stmt 1\n") : 0;
			freeform_new(&argsold,*old,pos);
			(debug==1) ? fprintf(stderr,"Debug : Survived freeform_new()\n") : 0;
//			size_argsold++;
//			write(&argsold[size_argsold],old);
			print(*argsold, debug);
		//	old = cur;
			pos++;
			curlvl = cur->lvl;
			(debug==1) ? fprintf(stderr,"Debug : Leaving if stmt 1\n\n") : 0;
		}else if(cur->lvl < curlvl){
/* If stmt 2 in the gameplan. If cur->lvl < curlvl, then we are going from
*  argument to command - Only possible way in which this can happen, 
*  something like cur(old,...). To evaluate, pull out the elements of 
*  argsold that are curlvl and send to evaluate. Because argsold gets 
*  selectively cleaned at the end of this block, the only nodes at curlvl
*  are the arguments of the command.
*/
			freeform_new(&argsold,*old,pos);
			pos++;
			(debug==1) ? fprintf(stderr,"Debug : Argsold at the start of if stmt 2\n") : 0;
			print(*argsold, debug);
			int size_args = 0;
			(debug==1) ? fprintf(stderr,"Debug : Entered if stmt 2\n") : 0;
			Input *tmp = argsold;
			Input *args=NULL;
			(debug==1) ? fprintf(stderr,"Debug : curlvl if stmt 2 : %d\n",curlvl) : 0;
			while(tmp!=NULL){
	//			printf("Debug : curlvl if stmt 2 : %d\n",curlvl);
				if(tmp->lvl == curlvl){
					freeform_new(&args,*tmp,size_args);
					size_args+=1;
				}
				tmp = tmp->prev;
//				printf("Debug : tmp --> tmp->prev\n");
			}

			(debug==1) ? fprintf(stderr,"Debug : Survived the args loop\n") : 0;
			argsold = selective_free(argsold,curlvl);
		//	printf("Debug : tmp = %p\n",argsold);	
			if(argsold!=NULL){
				(debug==1) ? fprintf(stderr,"Debug : Argsold in if stmt 2\n") : 0;
				print(*argsold, debug);
			}
/* 
*  Note : Author : OHR
*  For some reason, passing a null pointer to a function just leads straight to
*  a seg fault - even though I'm not using it. Anyone know why?
*/
			(debug==1) ? fprintf(stderr,"Debug : Survived the selective_free\n") : 0;
			evaluate(cur,args,Player,PlayerSize,S,debug);
			Free(args);
			(debug==1) ? fprintf(stderr,"Debug : Freed args\n") : 0;
			curlvl = cur->lvl;
			(debug==1) ? fprintf(stderr,"Debug : Leaving if stmt 2\n\n") : 0;
		}else{
/* If stmt 3 in the gameplan. If curlvl doesn't change, then we're looking at
*  another argument. Write to argsold and get on with life ;-)
*/
			(debug==1) ? fprintf(stderr,"Debug : Entered if stmt 3\n") : 0;
			(debug==1) ? fprintf(stderr,"Debug : Survived Realloc if stmt 3\n") : 0;
			freeform_new(&argsold,*old,pos);
			(debug==1) ? fprintf(stderr,"Debug : Survived freeform_new() if stmt 3\n") : 0;
			pos++;
			print(*argsold, debug);
			curlvl = cur->lvl;
			(debug==1) ? fprintf(stderr,"Debug : Leaving if stmt 3\n\n") : 0;
		}
//		sequential_print(argsold,size_argsold);
		old = cur;
		cur = cur->prev;	
	}
	Free(argsold);
	(debug==1) ? fprintf(stderr,"Debug : Freed argsold\n") : 0;
	(debug==1) ? fprintf(stderr,"Debug : Survived the parse loop!\n") : 0;
	return In;	
}
