/* move.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
* 
*  Abhirath Mahipal
*  abhirathmahipal@hotmail.com
*
*  (Sign in your name here if you make changes)
*  Move functions
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
		case (int)'w':
			if(C->y-1 != -1){
				M->cell[GRID_X*(C->y)+C->x].type = 0;
				C->y -= 1;
				place_on_map(*C,M);
				return 0;
			}else
				return 1;
			break;
		case (int)'s':
			if(C->y+1 != ROW-1-ROW_START){
				M->cell[GRID_X*(C->y)+C->x].type = 0;
				C->y += 1;
				place_on_map(*C,M);
				return 0;
			}else
				return 1;
			break;
		case (int)'a':	
			if(C->x-1 != -1){
				M->cell[GRID_X*(C->y)+C->x].type = 0;
				C->x -= 1;
				place_on_map(*C,M);
				return 0;
			}else
				return 1;
			break;
		case (int)'d':
			if(C->x+1 != COL-1-COL_START){
				M->cell[GRID_X*(C->y)+C->x].type = 0;		
				C->x += 1;
				place_on_map(*C,M);
				return 0;
			}else
				return 1;
			break;
		case KEY_UP:
			if(C->y-1 != -1){
				M->cell[GRID_X*(C->y)+C->x].type = 1;
				C->y -= 1;
				place_on_map(*C,M);
				return 0;
			}else
				return 1;
			break;
		case KEY_DOWN:
			if(C->y+1 != ROW-1-ROW_START){
				M->cell[GRID_X*(C->y)+C->x].type = 1;
				C->y += 1;
				place_on_map(*C,M);
				return 0;
			}else
				return 1;
			break;
		case KEY_LEFT:	
			if(C->x-1 != -1){
				M->cell[GRID_X*(C->y)+C->x].type = 1;
				C->x -= 1;
				place_on_map(*C,M);
				return 0;
			}else
				return 1;
			break;
		case KEY_RIGHT:
			if(C->x+1 != COL-1-COL_START){
				M->cell[GRID_X*(C->y)+C->x].type = 1;		
				C->x += 1;
				place_on_map(*C,M);
				return 0;
			}else
				return 1;
			break;
		case (int)'q':
			move(ROW-1,0);
			return 2;
		default:
			return 1;
	}
}
