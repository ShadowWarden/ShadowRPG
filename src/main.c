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
// Some const int can probably be replaced by defines

// Deciding each tile's width and heigh here. It can be changed in one shot in case we 
// decide to changed it later on

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define WIDTH_BLOCKS 64
#define HEIGHT_BLOCKS 48
#define TEXTURE_COUNT 128 // right now equal to ASCII chars
#define MAP_BUFFER_HEIGHT 2000
#define MAP_BUFFER_WIDTH 2000
int BUFFER_RELATIVE_TOP = 0;
int BUFFER_RELATIVE_LEFT = 0;
short int MAP_BUFFER[MAP_BUFFER_HEIGHT][MAP_BUFFER_WIDTH]; // holding a temporary buffer of 2K x 2k map tiles so that file operations are reduced
const char* MAP_DIR = "../resources/maps/"; // concatenate map instead of having to type it everytime
int PLAYER_X = -1; // map isn't loaded yet
int PLAYER_Y = -1; // map isn't loaded yet
char CURRENT_MAP[50] = "nomaploadedyet"; // assuming each map name is within 50 characters. Will be used to detect a change in map using the map name
const char EMPTY_TILE = '0';

// print map only handles printing. not concerned with the map text file. Have to change it
// get_map_content gets the current position of the player and gets the needed 1000 * 1000 tiles everytime
// the user approached the end
void load_all_textures(SDL_Texture *textures_holder[], SDL_Renderer*);
void initialise_map(SDL_Rect MAP_DISPLAY[HEIGHT_BLOCKS][WIDTH_BLOCKS]);
void load_map_buffer(char* map_file);
void print_map(SDL_Texture *textures_holder[], SDL_Renderer*, SDL_Rect MAP_DISPLAY[HEIGHT_BLOCKS][WIDTH_BLOCKS]);
void get_input(SDL_Window* window);

int main(int argc, char **argv){


	// As of now we support 128 different textures i.e ASCII Characters

	// should we move the relevant stuff to the global scope?
	SDL_Window* window;
	SDL_Renderer* renderer;	
	SDL_Texture* textures_holder[TEXTURE_COUNT];
	SDL_Rect MAP_DISPLAY[HEIGHT_BLOCKS][WIDTH_BLOCKS];
	

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
			initialise_map(MAP_DISPLAY);
			print_map(textures_holder, renderer, MAP_DISPLAY);
            SDL_UpdateWindowSurface(window);
           
        }
    }

    // main while loop
    while(true){
    	get_input(window);
		print_map(textures_holder, renderer, MAP_DISPLAY);
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
	textures_holder[53] = IMG_LoadTexture(renderer, "../resources/textrues/water.png");
}

void initialise_map(SDL_Rect MAP_DISPLAY[HEIGHT_BLOCKS][WIDTH_BLOCKS]) {
	// Setting the rectangle sizes and dimensions
	for (int row_iter = 0; row_iter < HEIGHT_BLOCKS; row_iter++){
		for (int col_iter = 0; col_iter < WIDTH_BLOCKS; col_iter++){
			MAP_DISPLAY[row_iter][col_iter].x = col_iter * 10;
			MAP_DISPLAY[row_iter][col_iter].y = row_iter * 10;
			MAP_DISPLAY[row_iter][col_iter].w = 10;
			MAP_DISPLAY[row_iter][col_iter].h = 10;
		}
	}
}

void print_map(SDL_Texture *textures_holder[], SDL_Renderer* renderer, SDL_Rect MAP_DISPLAY[HEIGHT_BLOCKS][WIDTH_BLOCKS]){

	load_map_buffer("randomshitfornow");
	short int map_element;

	for (int row_iter = 0; row_iter < HEIGHT_BLOCKS; row_iter++) {
		for (int col_iter = 0; col_iter < WIDTH_BLOCKS; col_iter++) {		

			map_element = MAP_BUFFER[row_iter + BUFFER_RELATIVE_TOP][col_iter + BUFFER_RELATIVE_LEFT];
			// could have used a switch case. But switch case labels have to be hard coded.
			// We therefore cannot use EMPTY_TILE instead of '0' in a switch case
			if (map_element == EMPTY_TILE) {
				break;
			}
			else {
				SDL_RenderCopy(renderer, textures_holder[map_element], NULL, &MAP_DISPLAY[row_iter][col_iter]);        
	  			SDL_RenderPresent(renderer);
			}				

		}
	}	

}

void load_map_buffer(char* map_file) {

	//TODO:- Check for change in map. right now just using the same test map

	// Read the max dimensions from the first two lines and
	// then allocate a 2-D array and continue from there
	
	FILE *fin = fopen("../resources/maps/test/2000x2000.map", "r");
	int row_count = 0, col_count = 0;
	short int map_element;
	
	fscanf(fin, "%d %d\n", &row_count, &col_count);
	
	int row = 0, col = 0;
	while((map_element = fgetc(fin)) != EOF){	
		// Reading from file and storing it in a data structure
		if (map_element == 10){
			while (col < MAP_BUFFER_WIDTH)
				MAP_BUFFER[row][col++] = EMPTY_TILE;
			row++; col = 0;
		}
		else{
			MAP_BUFFER[row][col++] = map_element;
		}
	}
	// filling the last row with zeroes in case it doesn't satify the buffer.
	while(col < MAP_BUFFER_WIDTH)
		MAP_BUFFER[row][col++] = EMPTY_TILE;

    // Filling in the rest of the buffer with zeroes
	col = 0;
    while(row < MAP_BUFFER_HEIGHT){
		while(col < MAP_BUFFER_WIDTH)
			MAP_BUFFER[row][col++] = EMPTY_TILE;
        row++;
	}


	fclose(fin);

	// Test printing the map
	FILE *fout = fopen("test.txt", "w");
	//fprintf(fout, "%d %d\n", row_count, col_count);
	for (int i = 0; i < MAP_BUFFER_WIDTH; i++){
		for (int j = 0; j < MAP_BUFFER_WIDTH; j++)
			fprintf(fout, "%c", MAP_BUFFER[i][j]);
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
						BUFFER_RELATIVE_TOP++;
                    break;

                    case SDLK_d:
                    case SDLK_RIGHT:
						BUFFER_RELATIVE_LEFT++;
                    break;

                    case SDLK_a:
                    case SDLK_LEFT:
						BUFFER_RELATIVE_LEFT--;
                    break;

                    case SDLK_w:
                    case SDLK_UP:
						BUFFER_RELATIVE_TOP--;
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
