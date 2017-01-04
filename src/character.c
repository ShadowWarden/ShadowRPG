/* character.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  (Sign in your name here if you make changes)
*  Vishnu Sharma
*  vishnu.rk1995@gmail.com
*  This file contains routine that are specifically meant for creation and 
*  function of the player character. For NPCs, use npc.c. This also includes
*  definitions character encumberance, etc.
*
*
*  This project is under the GNU General GPL version 3.0 license. For more 
*  information about the license, refer the LICENCE file in the root directory 
*  or go online to <http://www.gnu.org/licenses>
*  
*  Any redistribution of this code must contain this header in its entirety
*/

#include <stdio.h>
#include <ncurses.h>
#include "shadowengine.h"

#define INT_SIZE 4

// IMPROVE THESE TWO FUNCTIONS ASAP

int read_chars(Char *C){
	int i;
	char path[]="../data/character/char-1001.ch";//Originally ./data/
	FILE *fin;
	if(!(fin = fopen(path,"r"))){
		return 1;
	}
//	printf("Here!\n");
	int temp;
	char throw[20];
	fscanf(fin,"%s %d\n",throw,&(C->id));
	fscanf(fin,"%s %s\n",throw,C->first);
	fscanf(fin,"%s %s\n",throw,C->last);
	fscanf(fin,"%s %d\n",throw,&temp);
	fscanf(fin,"%s %d\n",throw,&temp);
	fscanf(fin,"%s %d\n",throw,&(C->st));
	fscanf(fin,"%s %d\n",throw,&(C->dx));
	fscanf(fin,"%s %d\n",throw,&(C->iq));
	fscanf(fin,"%s %d\n",throw,&(C->ch));
	fscanf(fin,"%s %d\n",throw,&(C->hpts));
	fscanf(fin,"%s %d\n",throw,&(C->lvl));
	fscanf(fin,"%s %d\n",throw,&(C->mapid));
	fscanf(fin,"%s %d\n",throw,&temp);
//	char junk;
//	printf("%d\n",temp);
//	scanf("%c",&junk);
	C->x = temp;
	fscanf(fin,"%s %d\n",throw,&temp);
	C->y = temp;
	fclose(fin);
	return 0;
}
 
int place_on_map(Char C, Map *M){
//	printf("%d %d",C.x,C.y);
//	char junk;
//	scanf("%c",&junk);
	M->cell[C.y*GRID_X+C.x].type=2;
	return 0;
}
