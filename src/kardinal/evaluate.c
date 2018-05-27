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


int evaluate(Input * In, Input * args, SymTable *S, int line, int * num_temp_variables, int debug){
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
	print(*args,debug);
	In->type = 0;
	if(EQSTR(In->name,"all")){
		All(In,args,debug);
	}else if(EQSTR(In->name,"some")){
		int res = Some(In,args,debug);
		if(res == -1){
			fprintf(stderr,"Error in some (Line %d): some failed with error code %d - Limit not specified or wrong type\n",line,res);
			return res;
		}
	}else if(EQSTR(In->name,"not")){
/* Note to NearlyHeadless : Do an errorcheck for number of arguments here. 
*  There should be exactly 1 and no more. I'm just spitting out a warning in
*  this version of the code here :
*/
		Not(In,args,debug);
	}else if(EQSTR(In->name, "setvar")){
		int result = -setvar(S,&args,debug);
		if(result != 0){
			fprintf(stderr,"Error in setvar (Line %d): Setvar failed with error code %d. Look at the documentation to troubleshoot\n",line,-result);
			return result;
		}else{
			strcpy(In->name,"true");
		}
		args=args->prev;
	}else if(EQSTR(In->name, "EQ")){
		VariableDec * Var1, * Var2; 
		int res;
		int res1 = find_in_hash(&Var1, *S,args->name);
		args = args->prev;
		int res2 = find_in_hash(&Var2, *S,args->name);
		if((res1 == 0 || res1 == 102) && (res2 == 0 || res2 == 0))
			res = EQ(Var1,Var2,debug);
		else{	
			fprintf(stderr,"Error in EQ (Line %d): EQ failed with error code 101. Look at the documentation to troubleshoot\n",line);
			return 101;
		}
			/* Change this ASAP so that it actually checks to make
			 * sure that res1/res2=101
			 */
		if(res1 == 102){
			/* Tmp was allocated to Var1 */
			free(Var1->value);
			free(Var1);
		}
		if(res2 == 102){
			free(Var2->value);
			free(Var2);
		}
		if(res == 0)
			strcpy(In->name,"true");
		else if(res == -1){
			strcpy(In->name,"false");
		}else{
			fprintf(stderr,"Error in EQ (Line %d): EQ failed with error code %d. Look at the documentation to troubleshoot\n",line,-res);
			return res;
		}
		/* Need to do an error condition here */
	}else if(EQSTR(In->name, "GE")){
		VariableDec * Var1, * Var2; 
		int res;
		int res1 = find_in_hash(&Var1, *S,args->name);
		args = args->prev;
		int res2 = find_in_hash(&Var2, *S,args->name);
		if((res1 == 0 || res1 == 102) && (res2 == 0 || res2 == 0))
			res = GE(Var1,Var2,debug);
		else{	
			fprintf(stderr,"Error in GE (Line %d): GE failed with error code 101. Look at the documentation to troubleshoot\n",line);
			return 101;
		}
			/* Change this ASAP so that it actually checks to make
			 * sure that res1/res2=101
			 */
		if(res1 == 102){
			/* Tmp was allocated to Var1 */
			free(Var1->value);
			free(Var1);
		}
		if(res2 == 102){
			free(Var2->value);
			free(Var2);
		}		
		if(res == 0)
			strcpy(In->name,"true");
		else if(res==-1)
			strcpy(In->name,"false");
		else{
			fprintf(stderr,"Error in GE (Line %d): GE failed with error code %d. Look at the documentation to troubleshoot\n",line,-res);
			return res;
		}
	}else if(EQSTR(In->name, "LE")){
		VariableDec * Var1, * Var2; 
		int res;
		int res1 = find_in_hash(&Var1, *S,args->name);
		args = args->prev;
		int res2 = find_in_hash(&Var2, *S,args->name);
		if((res1 == 0 || res1 == 102) && (res2 == 0 || res2 == 0))
			res = LE(Var1,Var2,debug);
		else{	
			fprintf(stderr,"Error in LE (Line %d): LE failed with error code 101. Look at the documentation to troubleshoot\n",line);
			return 101;
		}
			/* Change this ASAP so that it actually checks to make
			 * sure that res1/res2=101
			 */
		if(res1 == 102){
			/* Tmp was allocated to Var1 */
			free(Var1->value);
			free(Var1);
		}
		if(res2 == 102){
			free(Var2->value);
			free(Var2);
		}
		if(res == 0)
			strcpy(In->name,"true");
		else if(res == -1)
			strcpy(In->name,"false");
		else{
			fprintf(stderr,"Error in LE (Line %d): LE failed with error code %d. Look at the documentation to troubleshoot\n",line,-res);
			return res;
		}
	}else if(EQSTR(In->name, "print")){
		int res = Print(args,*S,debug);
		if(res == 0)
			strcpy(In->name,"true");
		else{
			fprintf(stderr,"Error in print (Line %d): print failed with error code %d. Look at the documentation to troubleshoot\n",line,res);
			return res;
		}
	}else if(EQSTR(In->name, "if")){
		int res = If(args, debug);
		if(res == 0){
		/* Error code 202 is if/true. 201 is false */
			return 202;
		}else if(res == -1){
			return 201;
		}else{
			fprintf(stderr,"Error in If (Line %d): print failed with error code %d. Look at the documentation to troubleshoot\n",line,res);
			return res;
		}
	}else if(EQSTR(In->name, "endif")){
		return -202;
	}else if(EQSTR(In->name, "+")){
		VariableDec * Var1, * Var2; 
		char *res;
		int res1 = find_in_hash(&Var1, *S,args->name);
		args = args->prev;
		int res2 = find_in_hash(&Var2, *S,args->name);
		if((res1 == 0 || res1 == 102) && (res2 == 0 || res2 == 0))
			res = Arith(0,S,Var1,Var2,num_temp_variables,debug);
		else{	
			fprintf(stderr,"Error in + (Line %d): + failed with error code 101. Look at the documentation to troubleshoot\n",line);
			return 101;
		}
			/* Change this ASAP so that it actually checks to make
			 * sure that res1/res2=101
			 */
		strcpy(In->name,res);	
	}else if(EQSTR(In->name, "-")){
		VariableDec * Var1, * Var2; 
		char *res;
		int res1 = find_in_hash(&Var1, *S,args->name);
		args = args->prev;
		int res2 = find_in_hash(&Var2, *S,args->name);
		if((res1 == 0 || res1 == 102) && (res2 == 0 || res2 == 0))
			res = Arith(1,S,Var1,Var2,num_temp_variables,debug);
		else{	
			fprintf(stderr,"Error in - (Line %d): - failed with error code 101. Look at the documentation to troubleshoot\n",line);
			return 101;
		}
			/* Change this ASAP so that it actually checks to make
			 * sure that res1/res2=101
			 */
		strcpy(In->name,res);	
	}else if(EQSTR(In->name, "*")){
		VariableDec * Var1, * Var2; 
		char *res;
		int res1 = find_in_hash(&Var1, *S,args->name);
		args = args->prev;
		int res2 = find_in_hash(&Var2, *S,args->name);
		if((res1 == 0 || res1 == 102) && (res2 == 0 || res2 == 0))
			res = Arith(2,S,Var1,Var2,num_temp_variables,debug);
		else{	
			fprintf(stderr,"Error in * (Line %d): * failed with error code 101. Look at the documentation to troubleshoot\n",line);
			return 101;
		}
			/* Change this ASAP so that it actually checks to make
			 * sure that res1/res2=101
			 */
		strcpy(In->name,res);	
	}else if(EQSTR(In->name, "/")){
		VariableDec * Var1, * Var2; 
		char *res;
		int res1 = find_in_hash(&Var1, *S,args->name);
		args = args->prev;
		int res2 = find_in_hash(&Var2, *S,args->name);
		if((res1 == 0 || res1 == 102) && (res2 == 0 || res2 == 0))
			res = Arith(3,S,Var1,Var2,num_temp_variables,debug);
		else{	
			fprintf(stderr,"Error in / (Line %d): / failed with error code 101. Look at the documentation to troubleshoot\n",line);
			return 101;
		}
			/* Change this ASAP so that it actually checks to make
			 * sure that res1/res2=101
			 */
		strcpy(In->name,res);	
	}else{
		fprintf(stderr,"Error in print (Line %d): print failed with error code 102 - Unknown reference to %s\n",line,In->name);
		return 102;
	}
		
	(debug==1) ? printf("Debug : Leaving Evaluate\n") : 0;
	return 0;
}
