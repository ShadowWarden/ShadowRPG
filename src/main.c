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
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "shadowengine.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char ** argv){


	// As of now we support 128 different textures i.e ASCII Characters
	// Screen size is 640 * 280 and each square is 20 X 20
	SDL_Window* window;
	SDL_Renderer* renderer;	
	SDL_Texture* texture[128];
	SDL_Rect rect[24][32];
    
    SDL_Surface* screenSurface = NULL;

    if( SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else{
        //Create window
        window = SDL_CreateWindow( "Shadow RPG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if(window == NULL){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else{
            
        	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        	texture[0] = IMG_LoadTexture(renderer, "grass.png");

        	for (int i = 0; i < 20; i++){
        		rect[0][i].x = i * 20;
        		rect[0][i].y = 0;
        		rect[0][i].w = 20;
        		rect[0][i].h = 20;	
            
	            SDL_RenderCopy(renderer, texture[0], NULL, &rect[0][i]);
	            
	            SDL_RenderPresent(renderer);

        	}
        	

        	

            SDL_UpdateWindowSurface(window);

            SDL_Delay(30000);
           
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();

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
