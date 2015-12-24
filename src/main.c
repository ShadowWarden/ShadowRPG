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
#include "shadowengine.h"

int main(int argc, char ** argv){
	// Declerations
	Map M;
	Char C;
	FILE *fin;
	char input;	

	// File pointer init
	fin = fopen("./resources/maps/test.map","r");
	map_read(fin,&M);
	read_chars(&C);
//	printf("%d\n",ret);
	place_on_map(C,&M);

//	print_deb(M);	
	initscr();
	curs_set(0);
	print_map(M);
	do{
		input = getch();	
		clear();
		int ret = action(&C,&M,input);
		if(ret){
			mvprintw(GRID_Y,0,"Can't do that!");
		}
		fflush(stdin);
		print_map(M);
		refresh();
	}while(input != 'q');
	endwin();
	
	fclose(fin);
	return 0;
}
