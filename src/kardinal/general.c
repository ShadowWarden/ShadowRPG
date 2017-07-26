/* kardinal/general.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  Vishnu Sharma
*  vishnu.rk1995@gmail.com
*
*  General functions (print, if - perhaps basic math functions like add)
*  should be defined here
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

int Print(VariableDec *A, int debug){
	// Compares A, B and returns 0 if equal
	if(A->value == NULL){
		(debug==1) ?fprintf(stderr,"Debug : First argument does not exist! Exiting\n") : 0;
		return -4;
	}else{
		if(strcmp(A->type,"int") == 0){
			fprintf(stdout,"%d",(int)*A->value);
		}else if(strcmp(A->type,"string")==0){
			printf("%s",*A->value);
		}	
	}
	return 0;
}


