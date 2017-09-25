/* kardinal/evaluate.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  Vishnu Sharma
*  vishnu.rk1995@gmail.com
*
*  Logic interface of the game. All available script
*  functions should be defined here in if statements
*
*  This project is under the GNU General GPL version 3.0 license. For more 
*  information about the license, refer the LICENCE file in the root directory 
*  or go online to <http://www.gnu.org/licenses>
*  
*  Any redistribution of this code must contain this header in its entirety
*/

#include"kardinal.h"

int All(Input *In, Input *args, int debug){
	(debug==1) ? fprintf(stderr,"Debug : Command is 'all'\n") : 0;
	int flag = 0;
	do{
		if(!EQSTR(args->name,"true")){
			flag++;
			(debug==1) ? fprintf(stderr,"Debug : %s is not true\n",args->name) : 0;
			strcpy(In->name,"false");
			//break;
			return -1;
		}
		args = args->prev;
	}while(args!=NULL);
	if(flag==0){
		strcpy(In->name,"true");	
	}
	(debug==1) ? fprintf(stderr,"Debug : Flag=%d, In.name=%s\n",flag,In->name) : 0;
	return 0;
}

int Some(Input *In, Input *args, int debug){
	(debug==1) ? fprintf(stderr,"Debug : Command is 'some'\n") : 0;
	int flag = 0,j;
	for(j=0;j<strlen(args->name);j++){
		if(!isdigit(args->name[j])){
			flag = 1;
			break;
		}
	}
	if(flag){
		return -1;
	}
	
	int lim = atoi(args->name);
	flag = 0;
	do{
		if(EQSTR(args->name,"true")){
			flag++;
			(debug==1) ? fprintf(stderr,"Debug : %s is true\n",args->name) : 0;	
		}
		if(flag == lim)
			break;
		args = args->prev;	
	}while(args!=NULL);
	if(flag==lim){
		strcpy(In->name,"true");	
	}else{
		strcpy(In->name,"false");
		return 1;
	}
	(debug==1) ? fprintf(stderr,"Debug : Flag=%d, In.name=%s\n",flag,In->name) : 0;
	return 0;
}
	
int Not(Input *In, Input *args, int debug){
	printf("Debug : Command is 'not'\n");
	if(args->prev!=NULL){
		(debug==1) ? fprintf(stderr,"Warning : Too many arguments. The code will act only on the last argument\n") : 0;
	}
	if(EQSTR(args->name,"true")){
		(debug==1) ? fprintf(stderr,"Debug : arg=%s\n",args->name) : 0;
		strcpy(In->name,"false");
	}else if(EQSTR(args->name,"false")){
		(debug==1) ? fprintf(stderr,"Debug : arg=%s\n",args->name) : 0;
		strcpy(In->name,"true");
	}
	else{
		(debug==1) ? fprintf(stderr,"Argument value neither true nor false") : 0;
		return -1;
	}	
	(debug==1) ? fprintf(stderr,"Debug : Arg=%s, In.name=%s\n",args->name,In->name) : 0;
	return 0;
}
