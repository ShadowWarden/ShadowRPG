/* main.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  Abhirath Mahipal
*  abhirathmahipal@hotmail.com
*
*  Vishnu Sharma
*  vishnu.rk1995@gmail.com
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
	// Declarations
	Map M;
	Char C;
	FILE *fin;
	char input;	

	// File pointer init
	fin = fopen("../resources/maps/test.map","r"); //Changed from ./resources/
	map_read(fin,&M);
	read_chars(&C);
//	printf("%d\n",ret);
	place_on_map(C,&M);

//	print_deb(M);	
	initscr();
	curs_set(0);
	header();
	keypad(stdscr,TRUE);
	cbreak();
	getch();
	clear();
	print_map(M);
	// Main game loop
	do{
		input = getch();	
		clear();
		int ret = action(&C,&M,input);
		if(ret){
			mvprintw(GRID_Y,0,"Can't do that!");
		}
		print_map(M);
		refresh();
		fflush(stdin);
	}while(input != 'q');
	endwin();
	
	fclose(fin);
	return 0;
}
