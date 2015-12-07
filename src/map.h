/* map.h
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  (Sign in your name here if you make changes)
*  Define structures, enum types, etc. for map generation
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
#define GRID_X 60
#define GRID_Y 22
#define ROW_START 1
#define COL_START 19

// Grid cell types for local maps
typedef enum local_type {
	FLOOR = 0,
	WALL = 1
}local_type;

// Grid cell types for entire maps
enum map_type{
	LOCAL = 0,
	OVERHEAD = 1
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


// Function declarations
int print_map(Map);
int map_read(FILE *,Map*);
