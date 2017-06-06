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

#define SIZE_DOUBLE 8

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

struct VariableDec{
	char varname[20]; 	// Variable Name
	char type[7];		// Variable Type
	char *value;		// Value
	int size; 		// Size in bytes
	struct VariableDec *prev;	// Pointer to the previous element
};

typedef struct Input Input;
typedef struct State State;
typedef struct VariableDec VariableDec;

// parse.c
Input * build(Input *, char *);
void Free(Input *);
void print(Input );
void print_final(Input );
Input * parse(Input *, State **, int *,VariableDec **, int *);

// evaluate.c
int evaluate(Input *, Input *, State **, int *, VariableDec **,int *);

// state.c
int build_states_test(FILE *);
int dump_states_test();
int find_ttl(int, State **, int *);
int add_state_to_player(int, State **, int *);
int remove_state_from_player(int, State **, int *);
int print_player_state(State *, int);

// variable.c
int getsize(FILE *);
int Free_var(VariableDec *);
void print_variable_stack(VariableDec);
int setvar(VariableDec **, int *,Input **);

// logical.c
int All(Input *, Input *);
int Some(Input *, Input *);
int Not(Input *, Input *);

//relational.c
int EQ(VariableDec *,VariableDec *);
int GE(VariableDec *,VariableDec *);
int LE(VariableDec *,VariableDec *);

// Extern variables
extern State * Titles;
extern int TitleSize;
