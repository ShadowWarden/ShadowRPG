#include<stdio.h>
#include<kardinal.h>
#include<stdlib.h>
#include<string.h>

int all(Input *In, Input *args){
	fprintf(stderr,"Debug : Command is 'all'\n");
	int flag = 0;
	do{
		if(!EQSTR(args->name,"true")){
			flag++;
			fprintf(stderr,"Debug : %s is not true\n",args->name);
			strcpy(In->name,"false");
			//break;
			return -1;
		}
		args = args->prev;
	}while(args!=NULL);
	if(flag==0){
		strcpy(In->name,"true");	
	}
	fprintf(stderr,"Debug : Flag=%d, In.name=%s\n",flag,In->name);
	return 0;
}

int some(Input *In, Input *args){
	fprintf(stderr,"Debug : Command is 'some'\n");
	int flag = 0;
	int lim = atoi(args->name);
	do{
		if(EQSTR(args->name,"true")){
			flag++;
			fprintf(stderr,"Debug : %s is true\n",args->name);	
		}
		args = args->prev;	
	}while(args!=NULL);
	if(flag==lim){
		strcpy(In->name,"true");	
	}else{
		strcpy(In->name,"false");
		return -1;
	}
	fprintf(stderr,"Debug : Flag=%d, In.name=%s\n",flag,In->name);
	return 0;
}
	
int not(Input *In, Input *args){
	printf("Debug : Command is 'not'\n");
	if(args->prev!=NULL){
		fprintf(stderr,"Warning : Too many arguments. The code will act only on the last argument\n");
	}
	if(EQSTR(args->name,"true")){
		fprintf(stderr,"Debug : arg=%s\n",args->name);
		strcpy(In->name,"false");
	}else if(EQSTR(args->name,"false")){
		fprintf(stderr,"Debug : arg=%s\n",args->name);
		strcpy(In->name,"true");
	}
	else{
		fprintf(stderr,"Argument value neither true nor false");
		return -1;
	}	
	fprintf(stderr,"Debug : Arg=%s, In.name=%s\n",args->name,In->name);
	return 0;
}
