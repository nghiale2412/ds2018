#include <stdio.h>
#include <rpc/rpc.h>
#include "file_transfer.h"

char file_name[100];
char *file_content;
FILE *file;

int * send_name_1_svc(char **argp, struct svc_req *rqstp){
	static int result;
	strcpy(file_name, *argp);
	printf("File name received %s \n", file_name);
	result = 1;
	return &result;
}

int * send_content_1_svc(char **argp, struct svc_req *rqstp){
	static int result;
	strcpy(file_content,*argp);
	file = fopen(file_name,"w");
	if (file==NULL)
	{
		result = 0;
		return(&result);
	}
	fprintf(file,"%s",file_content);
	fclose(file);
	result = 1;
	return(&result);
}