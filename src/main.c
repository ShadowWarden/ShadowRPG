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

// TODO:- Pass pointers instead of arrays and free memory as well
void load_all_textures(SDL_Texture *textures_holder[], SDL_Renderer*);
void print_map(char[], SDL_Texture *textures_holder[], SDL_Renderer*, SDL_Rect[24][32]);

int main(int argc, char ** argv){


	// As of now we support 128 different textures i.e ASCII Characters
	// Screen size is 640 * 280 and each square is 20 X 20

	// should we move the relevant stuff to the global scope?
	SDL_Window* window;
	SDL_Renderer* renderer;	
	SDL_Texture* textures_holder[128];
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
        	load_all_textures(textures_holder, renderer);

        	print_map("../resources/maps/test.map", textures_holder, renderer, rect);
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

void load_all_textures(SDL_Texture *textures_holder[], SDL_Renderer* renderer){

	// TODO find all files in the folder and load it one by one in the array
	// shift textures holder and rendered to the global scope?

	textures_holder[49] = IMG_LoadTexture(renderer, "../resources/textures/grass.png");
	textures_holder[50] = IMG_LoadTexture(renderer, "../resources/textures/env_grass_heather.png");
	textures_holder[51] = IMG_LoadTexture(renderer, "../resources/textures/env_redclay.png");
	textures_holder[52] = IMG_LoadTexture(renderer, "../resources/textures/carbon.png");
}

void print_map(char map[], SDL_Texture *textures_holder[], SDL_Renderer* renderer, SDL_Rect rect[24][32]){

	FILE *fin = fopen(map, "r");
	int map_element, row = 0, col = 0;

	while((map_element = fgetc(fin)) != EOF){

		
		// If it's a new line character go the next row and fill everything in this row with an empty rectangle
		if (map_element == 10){

			for (; col < 32; col++) {
				rect[row][col].x = col * 20;
				rect[row][col].y = row *20;
				rect[row][col].w = 20;
				rect[row][col].h = 20;

				//TODO:- something to these empty blocks soon. Probably fill it with a cross or something
			}

			row++;
			col = 0;

		}
		else{

			rect[row][col].x = col * 20;
			rect[row][col].y = row * 20;
			rect[row][col].w = 20;
			rect[row][col].h = 20;
			SDL_RenderCopy(renderer, textures_holder[map_element], NULL, &rect[row][col]);        
	        SDL_RenderPresent(renderer);
	        col++;

		}
	}

	fclose(fin);

}
