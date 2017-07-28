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
#define CAP 13
#define OFFSET 133

struct State{
	unsigned int id;
	char name[20];
	int attribute;
};

struct Input{
	char name[50];
	int type;     // 0 = Arg  ;  1 = Var
	int lvl;
	struct Input * prev;
//	int pos;
};

typedef struct VariableDec{
	char varname[20]; 	// Variable Name
	char type;		// Variable Type
	char *value;		// Value
//	int size; 		// Size in bytes
//	int level;
	struct VariableDec *prev;	// Pointer to the previous element
}VariableDec;

typedef struct SymbolTable{
	VariableDec *Vars[CAP];
	int level;
	struct SymbolTable * next;
}SymTable;

typedef struct Input Input;
typedef struct State State;

// parse.c
Input * build(Input *, char *);
void Free(Input *);
void print(Input, int);
void print_final(Input, int);
int parse(Input **, State **, int *,SymTable *, int, int);

// evaluate.c
int evaluate(Input *, Input *, State **, int *, SymTable *, int, int);

// state.c
int build_states_test(FILE *i, int);
int dump_states_test(int);
int find_ttl(int, State **, int *, int);
int add_state_to_player(int, State **, int *, int);
int remove_state_from_player(int, State **, int *, int);
int print_player_state(State *, int, int);
int getsize(FILE *);
//int Statecpy(State *, State *);

//variable.c
int Free_var(SymTable);
void print_variable_stack(SymTable);
int setvar(SymTable *,Input **, int);
int createhash(char *);
int add_to_table(SymTable *, VariableDec *);
int find_in_hash(VariableDec **, SymTable, char *);

// logical.c
int All(Input *, Input *, int);
int Some(Input *, Input *, int);
int Not(Input *, Input *, int);

//relational.c
int EQ(VariableDec *,VariableDec *, int);
int GE(VariableDec *,VariableDec *, int);
int LE(VariableDec *,VariableDec *, int);

//general.c
int Print(Input *, SymTable , int);
int If(Input *, int);

// Extern variables
extern State * Titles;
extern int TitleSize;
