/* kardinal/variable.c
 * Omkar H. Ramachandran
 * omkar.ramachandran@colorado.edu
 *
 * Main script parser/logic interface of the game. Do not edit this file unless 
 * absolutely necessary
 * 
 *
 * This project is under the GNU General GPL version 3.0 license. For more 
 * information about the license, refer the LICENCE file in the root directory 
 * or go online to <http://www.gnu.org/licenses>
 *  
 * Any redistribution of this code must contain this header in its entirety
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kardinal.h"

int Free_var(VariableDec * Vars){
	while(Vars!=NULL){
		free(Vars->value);
		VariableDec * tmp = Vars;
		Vars = Vars->prev;
		free(tmp);
	}
	free(Vars);
	return 0;
}

void print_variable_stack(VariableDec Vars, int debug){
	VariableDec * tmp = &Vars;
	(debug==1) ? fprintf(stderr,"Debug : Printing current variable stack\n") : 0;
	while(tmp!=NULL){
		(debug==1) ? fprintf(stderr,"Debug : %s : %s : %f : %d\n",tmp->varname,tmp->type,(float)*tmp->value,tmp->size) : 0;
		tmp=tmp->prev;
	}
	(debug==1) ? fprintf(stderr,"\n") : 0;
}


/* This is STRICTLY a work in progress function! The return type is Input * 
 *  because I didn't want to pass a pointer by reference (and thus work with
 *  a pointer to a pointer which is also a struct).
 *  If ANYONE has a better implementation, please implement it and send a 
 *  pull request to VariableSupportOHR
 */
int setvar(VariableDec ** Vars, int * size_var, Input ** args, int debug){
	VariableDec *var = (VariableDec*)malloc(sizeof(VariableDec));
	if(var == NULL){
		(debug==1) ? fprintf(stderr,"Error : Malloc returned NULL. Is there any memory left?\n") : 0;
		return -1;
	}
	(debug==1) ? fprintf(stderr,"Debug : New Variable Allocated\n") : 0;
	if(*size_var == 0){
		var->prev=NULL;
	}else{
		var->prev=*Vars;
	}
	*Vars=var;
	*size_var+=1;
	//Extract Args here
	strcpy(var->type,(*args)->name);
	(*args)=(*args)->prev;

	if(strcmp(var->type,"string")==0){
		var->value=(char *)malloc(sizeof(int));
		var->size=sizeof(char)*(strlen((*args)->name)+1);
	}else{
		var->value=NULL;
		var->size=0;
		(debug==1) ? fprintf(stderr,"Type not mentioned. Check documentation for syntax\n") : 0;
		return -2;
		/*
		 *  NearlyHeadless,
		 *  Someone needs to do an errorcheck on the default. Ideally,
		 *  we just shouldn't allow the type variable to be empty
		 */
	}
	// Compatible only for single float values
	if(strcmp(var->type,"string")==0){
		(debug==1) ? fprintf(stderr,"Debug : Assigning %s to var->value\n",(*args)->name) : 0;
		//strcpy(var->value,(*args)->name);	
		float intermediate_buffer;
		intermediate_buffer=atof((*args)->name);
		*var->value = intermediate_buffer;
		(debug==1) ? fprintf(stderr,"Debug: Assigned %f successfully\n",(float)*var->value) : 0;
		(*args) = (*args)->prev;
	}
	strcpy(var->varname,(*args)->name);

	return 0;
}