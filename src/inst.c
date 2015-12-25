/* move.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  (Sign in your name here if you make changes)
*  Instructions and version headers during development
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
#include <string.h>

void header(){
	char name[]="ShadowEngine v0.1.4";
	mvprintw(1,(COL-strlen(name))/2,name);
	mvprintw(3,0,"Features:");
	mvprintw(4,0,"   1. Printing out a map from data/");
	mvprintw(5,0,"   2. Added PC");
	mvprintw(6,0,"   3. Movable PC");
	mvprintw(9,0,"Use WASD to move, 'q' to quit");
	mvprintw(13,0,"List of known issues : ");
	mvprintw(14,0,"   1. Shift + WASD does not work");
	mvprintw(15,0,"   2. Arrow keys/Numpad do not work");
	refresh();
}
