/* genesis/map.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  (Sign in your name here if you make changes)
*  Has basic print/read functions on the map. I believe the function that 
*  actually places a character on the map is in another file (I think map.c?)
*
*  This project is under the GNU General GPL version 3.0 license. For more 
*  information about the license, refer the LICENSE file in the root directory 
*  or go online to <http://www.gnu.org/licenses>
*  
*  Any redistribution of this code must contain this header in its entirety
*/

#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include "shadowengine.h"

char print[3]={'.','#','@'};

int print_map(Map M){
	int row,col;
	int row_start,col_start;
	int i=0;
	
	getmaxyx(stdscr, row, col);
	if(row < GRID_Y){
		char mesg[] = "Variable screen sizes NOT supported in v0.0";
		mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
		return 1;
	}	
	while(i < GRID_X*GRID_Y){
		mvprintw(ROW_START+M.cell[i].x,COL_START+M.cell[i].y,"%c",print[M.cell[i].type]);
		i++;
	}
	return 0;
}

int map_read(FILE * fin,Map *M){
	int i,j;
	
	fseek(fin,SEEK_SET,0);
	fscanf(fin,"%d\n", &i);
	for(i=0;i<GRID_Y;i++){
		for(j=0;j<GRID_X;j++){
			int cur = GRID_X*i+j;
			int type;
			fscanf(fin,"%d ",&type);
			M->cell[cur].type=type;
			M->cell[cur].x = i;
			M->cell[cur].y = j;
		}
	}
	
	return 0;
}

int map_write(FILE * fout,Map *M){
	int i,j;

	fprintf(fout,"2\n");
	for(i=0;i<GRID_Y;i++){
		for(j=0;j<GRID_X;j++){
			int cur = GRID_X*i+j;
			fprintf(fout,"%d ",M->cell[cur].type);
		}
		fprintf(fout,"\n");
	}
	return 0;
}

int print_deb(Map M){
	int i=0,j;
	while(i<GRID_Y){
		j = 0;
		while(j<GRID_X){
			printf("%d ",M.cell[GRID_X*i+j].type);
			j++;
		}
		printf("\n");
		i++;
	}
}
