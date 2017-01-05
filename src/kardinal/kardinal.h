/* kardinal/kardinal.h
*
*  Main script parser/logic interface of the game. Do not edit this file unless 
*  absolutely necessary. Some functions here may need to be transferred to the 
*  main engine header file
*
*  This project is under the GNU General GPL version 3.0 license. For more 
*  information about the license, refer the LICENCE file in the root directory 
*  or go online to <http://www.gnu.org/licenses>
*  
*  Any redistribution of this code must contain this header in its entirety
*
*/

struct State{
	unsigned int id;
	char name[20];
	int attribute;
};

struct Input{
	char name[20];
	int type;     // 0 = Arg  ;  1 = Var
	int lvl;
	struct Input * prev;
//	int pos;
};

struct Var{
	char varname[20];
	char type[7];
	char value[8];
	Var *prev;
	Var *selfpointer;
};

typedef struct Input Input;
typedef struct State State;
typedef struct Var Var;

Input * build(Input *, char *);
void Free(Input *);
void print(Input );
void print_final(Input );
Input * parse(Input *, State **, int *);
int evaluate(Input *, Input *, State **, int *);
int build_states_test(FILE *);
int dump_states_test();
int add_state_to_player(int, State **, int *);
int print_player_state(State *, int);
int getsize(FILE *);

// Extern variables
extern State * Titles;
extern int TitleSize;
extern State * Players;
extern int PlayerSize;
