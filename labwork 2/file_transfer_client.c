#include <stdio.h>
#include <rpc/rpc.h>
#include "file_transfer.h"

int main(int argc,char *argv[])
{
	CLIENT *cl;
	char *server;
	int *result1;
	char *file_name;
	int *result2;
	char *file_content;
	char s[100];
	FILE *file;

	if(argc!=3){
		fprintf(stderr,  
        "usage: %s host message\n", argv[0]); 
        exit(1); 
	}
	server = argv[1];
	file_name = argv[2];
	cl = clnt_create(server,FILE_TRANSFER_PROG,FILE_TRANSFER_VERS,"tcp");
	if(cl == NULL)
	{
		clnt_pcreateerror(server);
		exit(1);
	}
	do
	{
		printf("Enter file name: ");
		scanf("%s",s);
		file_name = s;
		file = fopen(file_name, "r");
	}while(file == NULL);

	result1 = send_name_1(&file_name, cl);
	if(result1 == NULL)
	{
		clnt_perror(cl,server);
		exit(1);
	}
	result2 = send_content_1(&file_content,cl);
	if(result2 == NULL)
	{
		clnt_perror(cl,server);
		exit(1);
	}
	fclose(file);
	printf("File sent successfully to %s!\n", server);
	exit(0);
}