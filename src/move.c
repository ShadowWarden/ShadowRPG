/* move.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
* 
*  Abhirath Mahipal
*  abhirathmahipal@hotmail.com
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

int action(Char *C, Map *M,int input){
	switch(input){
		case 119:
		case KEY_UP:
			if(M->cell[GRID_X*(C->y-1)+C->x].type == 0){
				M->cell[GRID_X*(C->y)+C->x].type = 0;
				C->y -= 1;
				place_on_map(*C,M);
				return 0;
			}else
				return 1;
			break;
		case 115:
		case KEY_DOWN:
			if(M->cell[GRID_X*(C->y+1)+C->x].type == 0){
				M->cell[GRID_X*(C->y)+C->x].type = 0;
				C->y += 1;
				place_on_map(*C,M);
				return 0;
			}else
				return 1;
			break;
		case 97:	
		case KEY_LEFT:
			if(M->cell[GRID_X*(C->y)+C->x-1].type == 0){
				M->cell[GRID_X*(C->y)+C->x].type = 0;
				C->x -= 1;
				place_on_map(*C,M);
				return 0;
			}else
				return 1;
			break;
		case 100:
		case KEY_RIGHT:
			if(M->cell[GRID_X*(C->y)+C->x+1].type == 0){
				M->cell[GRID_X*(C->y)+C->x].type = 0;		
				C->x += 1;
				place_on_map(*C,M);
				return 0;
			}else
				return 1;
			break;
		default:
			return 1;
	}
}
