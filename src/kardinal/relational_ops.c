#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "variable.c"

int check_compatibility(VariableDec *VarsA, VariableDec *VarsB){
	if(VarsA->size != VarsB->size){
		printf("Size mismatch! Aborting!");
		return -1;
	}
	else {
		if(strcmp(VarsA->type,"string")==0){
			if(strcmp(VarsB->type,"string")!=0){
				printf("Type mismatch! Comparing String with non-String!");
				return 1;
			}
		}
		else if(strcmp(VarsA->type,"int")==0){
			if(strcmp(VarsB->type,"int")!=0){
				printf("Type mismatch! Comparing Integer with non-Integer!");
				return 2;
			}
		}
		else if(strcmp(VarsA->type,"double")==0){
			if(strcmp(VarsB->type,"double")!=0){
				printf("Type mismatch! Comparing Double with non-double!");
				return 3;
			}
		}
	}
	return 0;
}
int eq(VariableDec *VarsA, VariableDec *VarsB){
	int flag = check_compatibility(VarsA,VarsB);
	if (flag==0){
		if(strcmp(VarsA->value,VarsB->value)==0){
			printf("The variables are equal!");
			return 0;
			}
		else{
			printf("The variables aren't equal!");
			return -1;
		}
	}
	else return flag;
}
int lt(VariableDec *VarsA, VariableDec *VarsB){
	int flag = check_compatibility(VarsA,VarsB);
	if (flag==0){
		if(strcmp(VarsA->value,VarsB->value)<0){
			printf("The first variable is lesser!");
			return 0;
			}
		else{
			printf("Check failed!");
			return -1;
		}
	}
	else return flag;
}
int gt(VariableDec *VarsA, VariableDec *VarsB){
	int flag = check_compatibility(VarsA,VarsB);
	if (flag==0){
		if(strcmp(VarsA->value,VarsB->value)>0){
			printf("The first variable is greater!");
			return 0;
			}
		else{
			printf("Check failed!");
			return -1;
		}
	}
	else return flag;
}
int lte(VariableDec *VarsA, VariableDec *VarsB){
	if(eq(VarsA, VarsB)&&lt(VarsA,VarsB)==0){
		printf("First variable is less than or equal to the second!");
		return 0;	
	}
	else {
		printf("Check failed!");
		 return -1;
	}
}
int gte(VariableDec *VarsA, VariableDec *VarsB){
	if(eq(VarsA, VarsB)&&gt(VarsA,VarsB)==0){
		printf("First variable is greater than or equal to the second!");
		return 0;	
	}
	else {
		printf("Check failed!");
		 return -1;
	}
}
