/* kardinal/input.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  All IO functions for the script engine should be defined here
* 
*
*  This project is under the GNU General GPL version 3.0 license. For more 
*  information about the license, refer the LICENCE file in the root directory 
*  or go online to <http://www.gnu.org/licenses>
*  
*  Any redistribution of this code must contain this header in its entirety
*/

#include "kardinal.h"

int number_lines(FILE *fin){
	int num_lines = 0;
	char buffer[MAX_INPUT];

	while(fgets(buffer,MAX_INPUT,fin)){
		num_lines ++;
	}
	return num_lines;
}

char ** read_source(char ** line, FILE *fin){
/* Read in a line of source into a char buffer of size MAX_SIZE.
 * Ignore commented lines to save space.
 * Allocate MAX_SIZE*sizeof(char) bytes to line[lineindex] 
 * Copy over the stuff in the buffer to line[lineindex]
 * update lineindex
 */
	int lineindex = 0;
	char buffer[MAX_INPUT];
	
	fseek(fin,SEEK_SET,0);
	while(fgets(buffer,MAX_INPUT,fin)){
		line[lineindex] = (char *) malloc(MAX_INPUT*sizeof(char));
		strcpy(line[lineindex],buffer);
		lineindex += 1;
	}
	return line;
}

void Free_source(char ** line, int num_lines){
	int i;
	for(i=0;i<num_lines;i++){
		free(line[i]);
	}
}
