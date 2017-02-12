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
#include <string.h>
#include <stdbool.h>

// TODO create an enum to map numbers with texture names.

// Deciding each tile's width and heigh here. It can be changed in one shot in case we 
// decide to changed it later on

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int WIDTH_BLOCKS = 64;
const int HEIGHT_BLOCKS = 48;
const int TEXTURE_COUNT = 128; // right now equal to ASCII chars
const short int MAP_BUFFER[2000][2000]; // holding a temporary buffer of 2K x 2k map tiles so that file operations are reduced
const char* MAP_DIR = "../resources/maps/"; // concatenate map instead of having to type it everytime


// print map only handles printing. not concerned with the map text file. Have to change it
// get_map_content gets the current position of the player and gets the needed 1000 * 1000 tiles everytime
// the user approached the end
void load_all_textures(SDL_Texture *textures_holder[], SDL_Renderer*);
void get_map_content(char* map_file, int current_x, int current_y);
void print_map(char*, SDL_Texture *textures_holder[], SDL_Renderer*, SDL_Rect MAP_DISPLAY[HEIGHT_BLOCKS][WIDTH_BLOCKS]);
void get_input(SDL_Window* window);

int main(int argc, char **argv){


	// As of now we support 128 different textures i.e ASCII Characters

	// should we move the relevant stuff to the global scope?
	SDL_Window* window;
	SDL_Renderer* renderer;	
	SDL_Texture* textures_holder[TEXTURE_COUNT];
	SDL_Rect MAP_DISPLAY[WIDTH_BLOCKS][HEIGHT_BLOCKS];
	

    SDL_Surface* screenSurface = NULL;

    if( SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else{
        //Create window
        window = SDL_CreateWindow( "Shadow RPG", SDL_WINDOWPOS_UNDEFINED,
        								   		 SDL_WINDOWPOS_UNDEFINED, 
        								   		 SCREEN_WIDTH, SCREEN_HEIGHT, 
        								   		 SDL_WINDOW_SHOWN );
        if(window == NULL){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else{
            
        	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        	load_all_textures(textures_holder, renderer);
			print_map("test.map", textures_holder, renderer, MAP_DISPLAY);
            SDL_UpdateWindowSurface(window);
           
        }
    }

    // main while loop
    while(true){
    	get_input(window);
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

void print_map(char *map, SDL_Texture *textures_holder[], SDL_Renderer* renderer, SDL_Rect MAP_DISPLAY[HEIGHT_BLOCKS][WIDTH_BLOCKS]){

	// Read the max dimensions from the first two lines and
	// then allocate a 2-D array and continue from there
	
	FILE *fin = fopen("../resources/maps/test.map", "r");
	int row_count = 0, col_count = 0;
	short int map_element;
	
	fscanf(fin, "%d %d\n", &row_count, &col_count);
	// Possible improvements:- Use linked lists in case the map
	// is scarely filled
	short int map_representation[row_count][col_count];
	
	int row = 0, col = 0;
	while((map_element = fgetc(fin)) != EOF){	
		// Reading from file and storing it in a data structure
		if (map_element == 10){
			while (col < col_count)
				map_representation[row][col++] = '0';
			row++; col = 0;
		}
		else{
			map_representation[row][col++] = map_element;
		}
	}
	// filling the last row with zeroes in case it's empty
	while(col < col_count)
		map_representation[row][col++] = '0';

	fclose(fin);

	for (int row_iter = 0; row_iter < row_count; row_iter++) {
		for (int col_iter = 0; col_iter < col_count; col_iter++) {
			MAP_DISPLAY[row_iter][col_iter].x = col_iter * 10;
			MAP_DISPLAY[row_iter][col_iter].y = row_iter * 10;
			MAP_DISPLAY[row_iter][col_iter].w = 10;
			MAP_DISPLAY[row_iter][col_iter].h = 10;

			map_element = map_representation[row_iter][col_iter];
			switch (map_element) {
				case '0':
					break;

				default:
					SDL_RenderCopy(renderer, textures_holder[map_element], NULL, &MAP_DISPLAY[row_iter][col_iter]);        
	  			    SDL_RenderPresent(renderer);
			}			

		}
	}

		

	// Test printing the map
	FILE *fout = fopen("test.txt", "w");
	fprintf(fout, "%d %d\n", row_count, col_count);
	for (int i = 0; i < row_count; i++){
		for (int j = 0; j < col_count; j++)
			fprintf(fout, "%c", map_representation[i][j]);
        fprintf(fout,"\n");
	}
		

}

void get_input(SDL_Window *window){
    SDL_Event event;


    while (SDL_PollEvent(&event)) {

    	// Outer switch classifies events into keyboard, mouse etc
    	// Inner switch cases are more specific
        switch (event.type) {

        	// TODO:- A lot left. Just the basic outline
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        exit(0);
                    break;

                    case SDLK_s:
                    case SDLK_DOWN:
                    break;

                    case SDLK_d:
                    case SDLK_RIGHT:
                    break;

                    case SDLK_a:
                    case SDLK_LEFT:
                    break;

                    case SDLK_w:
                    case SDLK_UP:
                    break;

                    case SDLK_r:
                    break;

                    case SDLK_SPACE:
                    break;

                    default:
                    break;
                }
            break;

            case SDL_KEYUP:
            break;

            case SDL_USEREVENT:
            break;

            case SDL_MOUSEBUTTONDOWN:
            	switch (event.button.button){
            		case SDL_BUTTON_LEFT:
            			SDL_ShowSimpleMessageBox(0, "Mouse", "Left", window);
            			break;

            		case SDL_BUTTON_RIGHT:
            			SDL_ShowSimpleMessageBox(0, "Mouse", "Right", window);
            			break;

            		default:
            			SDL_ShowSimpleMessageBox(0, "Mouse", "Something Else", window);
            			break;
            	}

            default:
            break;
        }
    }
}
