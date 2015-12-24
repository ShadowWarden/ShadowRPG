/* move.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  (Sign in your name here if you make changes)
*  Player/NPC movement functions
*  
*  
*
*  This project is under the GNU General GPL version 3.0 license. For more 
*  information about the license, refer the LICENCE file in the root directory 
*  or go online to <http://www.gnu.org/licenses>
*  
*  Any redistribution of this code must contain this header in its entirety
*/

#include <ncurses.h>
#include "shadowengine.h"

int action(Char *C, Map *M,char input){
	if(input == 'w'){
		if(M->cell[GRID_X*(C->y-1)+C->x].type == 0){
			M->cell[GRID_X*(C->y)+C->x].type = 0;
			C->y -= 1;
			place_on_map(*C,M);
			return 0;
		}
	}
	if(input == 's'){
		if(M->cell[GRID_X*(C->y+1)+C->x].type == 0){
			M->cell[GRID_X*(C->y)+C->x].type = 0;
			C->y += 1;
			place_on_map(*C,M);
			return 0;
		}
	}
	if(input == 'a'){
		if(M->cell[GRID_X*(C->y)+C->x-1].type == 0){
			M->cell[GRID_X*(C->y)+C->x].type = 0;
			C->x -= 1;
			place_on_map(*C,M);
			return 0;
		}
	}
	if(input == 'd'){
		if(M->cell[GRID_X*(C->y)+C->x+1].type == 0){
			M->cell[GRID_X*(C->y)+C->x].type = 0;		
			C->x += 1;
			place_on_map(*C,M);
			return 0;
		}
	}
	return 1;
}
