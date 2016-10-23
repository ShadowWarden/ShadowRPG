/* map.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  (Sign in your name here if you make changes)
*  Map rendering code. Does File IO, object placement, object drops, damage (if
*  we implement that). Use the map code from 'Winter is coming' as a starting
*  point. Use the struct in map.h to store runtime info
*
*  This project is under the GNU General GPL version 3.0 license. For more 
*  information about the license, refer the LICENSE file in the root directory 
*  or go online to <http://www.gnu.org/licenses>
*  
*  Any redistribution of this code must contain this header in its entirety
*/

#include <stdio.h>
#include <string.h>
#include "shadowengine.h"

char print[3]={'.','#','@'};

int print_map(Map M){
	
}

int map_read(FILE * fin,Map *M){
	int i,j;
	
	fseek(fin,SEEK_SET,0);
	for(i=0;i<     FILLDIMENSIONHERE DUH;i++){
		for(j=0;j< XCOORDINATESHERE DUH;j++){
			int cur = GRID_X*i+j;
			int type;
			fscanf(fin,"%c",&type);
			// change texture accordingly
			cur++;
		}
	}
	
	return 0;
}

int print_debug(Map M){
	// prints out the type of the texture (number/name whatever)
}
