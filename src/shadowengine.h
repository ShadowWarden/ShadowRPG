/* shadowengine.h
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  Abhirath Mahipal
*  abhirathmahipal@hotmail.com
*
*  (Sign in your name here if you make changes)
*  Define structures, enum types, etc.
* 
* 
*
*  This project is under the GNU General GPL version 3.0 license. For more 
*  information about the license, refer the LICENSE file in the root directory 
*  or go online to <http://www.gnu.org/licenses>
*  
*  Any redistribution of this code must contain this header in its entirety
*/

#include <stdio.h>

// Defined datatypes
#define COL 80
#define ROW 24
#define GRID_X 60
#define GRID_Y 22
#define ROW_START 1
#define COL_START 19
#define MAXNAMELT 20
#define MAX_CHARS 1


// Grid cell types for local maps
typedef enum local_type {
	FLOOR = 0,
	WALL = 1,
	PLAYER = 2
}local_type;

// Grid cell types for entire maps
enum map_type{
	LOCAL = 0,
	OVERHEAD = 1
};

enum State{
        DEAD=0,
        ALIVE=1
};

enum Gender{
        MALE=0,
        FEMALE=1
};

enum Action{
	UP = 'w',
	DOWN = 's',
	LEFT = 'a',
	RIGHT = 'd'
};

// Structures
typedef struct{
	int x;
	int y;
	int type;	
}Cell;

typedef struct{
//	int id;
	Cell cell[GRID_X*GRID_Y];
//	map_type type; Include this later when you have different map types	
}Map;

// Add more params as the engine gets more complex
typedef struct{
        // ID
        int id;

        // Name and basic bio
        char first[MAXNAMELT];
        char last[MAXNAMELT];
        int G;
        int S;

        // Stats
        int st;
        int dx;
        int iq;
        int ch;
        int hpts;
        int lvl;

        // Map details
        int mapid;
        int x;
        int y;
}Char;


// Function declarations
int map_read(FILE *,Map*);
int read_chars(Char *);
int place_on_map(Char, Map *);
int action(Char *,Map *,int);
void header();
