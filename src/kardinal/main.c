/* kardinal/main.c
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
#include <string.h>
#include <stdlib.h>
#include "kardinal.h"

#define MAX_INPUT 100

int main(int argc, char ** argv){
	char input[100];
	State S={NULL,0};
	Input *In = (Input *) malloc (sizeof(Input));
//	In->prev = NULL;
	int i,err,maxlvl;
	int size_in = (MAX_INPUT>(sizeof(argv[1])))?MAX_INPUT:sizeof(argv[i]);
	printf("%s\n\n",argv[1]);
	for(i=0;i<size_in;i++){
		input[i] = argv[1][i];	
	}
	input[size_in]='\0';
	// Build the command stack
	In = build(In,input);
//	printf("%s : %d : %d : %s\n\n\n",In->name,In->lvl,In->type,In->prev->name);
	In = parse(In);
	print(*In);
//	scanf("%c",&junk);	
	Free(In);
	return 0;
}