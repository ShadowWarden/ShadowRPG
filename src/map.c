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
*  information about the license, refer the LICENCE file in the root directory 
*  or go online to <http://www.gnu.org/licenses>
*  
*  Any redistribution of this code must contain this header in its entirety
*/

#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include "map.h"

char print[2]={'.','#'};

int print_map(Map M){
	int row,col;
	int row_start,col_start;
	int i=0;
	
	getmaxyx(stdscr, row, col);
	if(row < GRID_DIM){
		char mesg[] = "Variable screen sizes NOT supported in v0.0";
		mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
		return 1;
	}	
	row_start = (row - GRID_DIM)/2;
	col_start = (col - 2*GRID_DIM)/2;
	
	while(i < GRID_DIM*GRID_DIM){
		mvprintw(row_start+M.cell[i].x,col_start+2*M.cell[i].y,"%c",print[M.cell[i].type]);
		i++;
	}
	return 0;
}

int map_read(FILE * fin,Map *M){
	int i,j;
	
	fseek(fin,SEEK_SET,0);
	fscanf(fin,"%d\n", &i);
	for(i=0;i<GRID_DIM;i++){
		for(j=0;j<GRID_DIM;j++){
			int cur = GRID_DIM*i+j;
			int type;
			fscanf(fin,"%d ",&type);
			M->cell[cur].type=type;
			M->cell[cur].x = i;
			M->cell[cur].y = j;
			cur++;
		}
	}
	
	return 0;
}

int print_deb(Map M){
	int i=0,j;
	while(i<GRID_DIM){
		j = 0;
		while(j<GRID_DIM){
			printf("%d ",M.cell[GRID_DIM*i+j].type);
			j++;
		}
		printf("\n");
		i++;
	}
}
