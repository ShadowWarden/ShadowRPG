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

#include <SDL2/SDL.h>
#include <stdio.h>
#include "shadowengine.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char ** argv){

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;
    
    SDL_Surface* screenSurface = NULL;

    if( SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else {
        //Create window
        window = SDL_CreateWindow( "Shadow RPG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if(window == NULL) {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else {
            
        	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            screenSurface = SDL_GetWindowSurface( window);

            
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
            
            SDL_UpdateWindowSurface(window);

            SDL_Delay(3000);
           
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    SDL_Quit();
    //IMG_Quit();

    return 0;
}



// 	// Declerations
// 	Map M;
// 	Char C;
// 	FILE *fin;
// 	char input;	

// 	// File pointer init
// 	fin = fopen("./resources/maps/test.map","r");
// 	map_read(fin,&M);
// 	read_chars(&C);
// //	printf("%d\n",ret);
// 	place_on_map(C,&M);

// //	print_deb(M);	
// 	initscr();
// 	curs_set(0);
// 	header();
// 	keypad(stdscr,TRUE);
// 	cbreak();
// 	getch();
// 	clear();
// 	print_map(M);
// 	// Main game loop
// 	do{
// 		input = getch();	
// 		clear();
// 		int ret = action(&C,&M,input);
// 		if(ret){
// 			mvprintw(GRID_Y,0,"Can't do that!");
// 		}
// 		print_map(M);
// 		refresh();
// 		fflush(stdin);
// 	}while(input != 'q');
// 	endwin();
	
// 	fclose(fin);
// 	return 0;
// }
