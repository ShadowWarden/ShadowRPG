/* main.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  (Sign in your name here if you make changes)
*  Everything has to come together here. No big function definitions here. 
*  This file should only contain the skeleton of the core game loop. Put 
*  any file that you want into the accompanying c files
*
*  This project is under the GNU General GPL version 3.0 license. For more 
*  information about the license, refer the LICENSE file in the root directory 
*  or go online to <http://www.gnu.org/licenses>
*  
*  Any redistribution of this code must contain this header in its entirety
*/

#include <stdio.h>
#include <ncurses.h>
#include "map.h"

int main(int argc, char ** argv){
	// Declerations
	Map M;
	FILE *fin;
	char junk;	

	// File pointer init
	fin = fopen("./artlib/resources/maps/test.map","r");
	map_read(fin,&M);

//	print_deb(M);	
	initscr();
	print_map(M);
	refresh();
	getch();
	endwin();
	
	fclose(fin);
	return 0;
}
