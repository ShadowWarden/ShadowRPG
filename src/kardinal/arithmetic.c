/* kardinal/arithmetic.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  Vishnu Sharma
*  vishnu.rk1995@gmail.com
*
*  General math functions (basic math operations like +, -, / and *)
*  should be defined here
*
*  This project is under the GNU General GPL version 3.0 license. For 
*  more information about the license, refer the LICENCE file in the 
*  root directory or go online to <http://www.gnu.org/licenses>
*  
*  Any redistribution of this code must contain this header in its 
*  entirety
*/

#include<stdio.h>
#include"kardinal.h"
#include<stdlib.h>
#include<string.h>

char * Add(SymTable * S, VariableDec * Var1, VariableDec * Var2, int * num_temp_variables,int debug){
	if(Var1->type != 'i' || Var2->type != 'i'){
		return NULL;
	}
	
	VariableDec * Res = (VariableDec *) malloc (sizeof(VariableDec));
	Res->type = 'i';
	Res->value = (char *) malloc (sizeof(int));
	*Res->value = (int)(*Var1->value)+(int)(*Var2->value);
	char resname[12];
	snprintf(resname,12,"__tmp%d",*num_temp_variables);
	*num_temp_variables += 1;
	strcpy(Res->varname,resname);
	Res->prev = NULL;

	int hashkey = createhash(resname);
	if(S->Vars[hashkey] == NULL){
		S->Vars[hashkey] = Res;
	}else{
		VariableDec * tmp = S->Vars[hashkey];
		while(tmp->prev != NULL){
			tmp = tmp->prev;
		}
		tmp->prev = Res;
	}
	
	return Res->varname;	
}
