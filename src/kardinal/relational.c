/* kardinal/evaluate.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  Vishnu Sharma
*  vishnu.rk1995@gmail.com
*
*  Relational operator interface of the game. All available script
*  functions should be defined here in if statements
*
*  This project is under the GNU General GPL version 3.0 license. For more 
*  information about the license, refer the LICENCE file in the root directory 
*  or go online to <http://www.gnu.org/licenses>
*  
*  Any redistribution of this code must contain this header in its entirety
*/

#include<stdio.h>
#include"kardinal.h"
#include<stdlib.h>
#include<string.h>

#define EQSTR(a,b) (strcmp(a,b)==0)

int EQ(VariableDec *A, VariableDec *B){
	// Compares A, B and returns 0 if equal
	fprintf(stderr,"Debug : Command is 'EQ'. Comparing %f and %f\n",(float)*A->value,(float)*B->value);
	if(A->value == NULL){
		fprintf(stderr,"Debug : First argument does not exist! Exiting\n");
		return -4;
	}
	else if(B->value == NULL){
		fprintf(stderr,"Debug : Second argument does not exist! Exiting\n");
		return -3;
	}
	else{
		if(strcmp(A->type,B->type)==0){
			if(strcmp(A->type,"string")==0){
				if(*A->value == *B->value){
					fprintf(stderr,"Debug : The values are equal!\n");
					return 0;
				}
				else{
					fprintf(stderr,"Debug : The values fail the comparison!\n");
					return -1;
				}
			}
			else{
				fprintf(stderr,"Type not mentioned. Check documentation for syntax\n");
				return 1;
			}
		}
		else{
			fprintf(stderr,"Debug : Type mismatch. Check inputs\n");
			return -2;
		}
	}
}

int GE(VariableDec *A, VariableDec *B){
	// Compares A, B and returns 0 if A greater than or equal to B
	fprintf(stderr,"Debug : Command is 'GE_or_EQ'. Comparing %f and %f\n",(float)*A->value,(float)*B->value);
	if(A->value == NULL){
		fprintf(stderr,"Debug : First argument does not exist! Exiting\n");
		return -4;
	}
	else if(B->value == NULL){
		fprintf(stderr,"Debug : Second argument does not exist! Exiting\n");
		return -3;
	}
	else{
		if(strcmp(A->type,B->type)==0){
			if(strcmp(A->type,"string")==0){
				if(*A->value > *B->value){
					fprintf(stderr,"Debug : The first value is greater than or equal to the second!\n");
					return 0;
				}
				else{
					fprintf(stderr,"Debug : The values fail the comparison!\n");
					return -1;
				}
			}
			else{
				fprintf(stderr,"Type not mentioned. Check documentation for syntax\n");
				return 1;
			}
		}
		else{
			fprintf(stderr,"Debug : Type mismatch. Check inputs\n");
			return -2;
		}
	}
}

int LE(VariableDec *A, VariableDec *B){
	// Compares A, B and returns 0 if A lesser than or equal B
	fprintf(stderr,"Debug : Command is 'LE_or_EQ'. Comparing %f and %f\n",(float)*A->value,(float)*B->value);
	if(A->value == NULL){
		fprintf(stderr,"Debug : First argument does not exist! Exiting\n");
		return -4;
	}
	else if(B->value == NULL){
		fprintf(stderr,"Debug : Second argument does not exist! Exiting\n");
		return -3;
	}
	else{
		if(strcmp(A->type,B->type)==0){
			if(strcmp(A->type,"string")==0){
				if(*A->value < *B->value){
					fprintf(stderr,"Debug : The first value is lesser than or equal to the second!\n");
					return 0;
				}
				else{
					fprintf(stderr,"Debug : The values fail the comparison!\n");
					return -1;
				}
			}
			else{
				fprintf(stderr,"Type not mentioned. Check documentation for syntax\n");
				return 1;
			}
		}
		else{
			fprintf(stderr,"Debug : Type mismatch. Check inputs\n");
			return -2;
		}
	}
}
