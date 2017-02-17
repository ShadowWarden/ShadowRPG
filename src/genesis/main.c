/* main.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  Abhirath Mahipal
*  abhirathmahipal@hotmail.com
*
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
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "shadowengine.h"

int main(int argc, char ** argv){
	// Declerations
	Map M;
	Char C;
	FILE *fin;
	FILE *fout;
	int input;
	char out[50]="./resources/maps/";	
	char file[25];
	char fileout[25];

	// File pointer init
	printf("Enter name of input map file : ");
	scanf("%s",file);
	strcat(out,file);
	fin = fopen(out,"r");
	if(!fin){
		printf("Cannot open file. Does it exist?\n");
		exit(1);
	}
	strcpy(out,"./resources/maps/");
	map_read(fin,&M);
	read_chars(&C);
//	printf("%d\n",ret);
	place_on_map(C,&M);
	fclose(fin);
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
		if(ret == 1){
			mvprintw(GRID_Y,0,"Can't do that!");
		}else if(ret == 2){
			mvprintw(GRID_Y,0,"Save as : ");
			getstr(fileout);
		}
		print_map(M);
		refresh();
		fflush(stdin);
	}while(input != 'q');
	remove_from_map(C,&M);
	endwin();
	strcat(out,fileout);	
	fout = fopen(out,"w");
	map_write(fout,&M);

	fclose(fout);
	return 0;
}
