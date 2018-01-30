#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mpi.h"


int main(int argc, char *argv[])
{
	FILE *f;
	//the tag of the message, identify the meaning of message
	int tagContent, tagName, tagContentSize;
	tagContent = 1;
	tagName = 2;
	tagContentSize = 3;
	
	//destination, which rank to send
	int dest = 1;
	int source = 0;

	//initialize
	MPI_Init(&argc, &argv);
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	while(1){
		if (world_rank == 0 ){ //send file 
			printf("This is Send\n");
			//read file
			int c,temp;
			temp=0;
			char fileName[100];
			printf("Enter name of the file to send :\n");
			scanf("%s", fileName);
			f = fopen(fileName,"r");
		
			//get the length of file's content + filename
			size_t pos = ftell(f);    // Current position
			fseek(f, 0, SEEK_END);    // Go to end
			size_t length = ftell(f); // read the position which is the size
			fseek(f, pos, SEEK_SET);
			int lengthContent = sizeof(length)/sizeof(size_t);	

			//allocate data into string
			char *content;
			content = (char *) malloc(length*sizeof(char));
			if (f){
            while((c = getc(f))!=EOF)
                content[temp++] = c;
        	}
			fclose(f);
			
			//send using mpi
			MPI_Send(&lengthContent, sizeof(lengthContent)/sizeof(int), MPI_INT, dest, tagContentSize, MPI_COMM_WORLD);
			
			MPI_Send(fileName, sizeof(fileName)/sizeof(char), MPI_CHAR, dest, tagName, MPI_COMM_WORLD);
			MPI_Send(content, sizeof(content)/sizeof(char), MPI_CHAR, dest, tagContent, MPI_COMM_WORLD);
			printf("Send successfuly\n");
		}else if (world_rank == 1) { //receive file 	
			printf("This is Receive\n");	

			char directoryTemp[] = "receive/";
			char fileName[100];
			
			//recv using mpi
			int lengthContent;
			
			//recv length of the contents
			MPI_Recv(&lengthContent, 100, MPI_INT, source, tagContentSize, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			
			//allocate for the contents of file
			char *tempContent;
			tempContent = (char *) malloc(sizeof(char)*lengthContent);
			
			//recving file content including name
			MPI_Recv(fileName, 100, MPI_CHAR, source, tagName, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			strcat(directoryTemp,fileName);
			MPI_Recv(tempContent, lengthContent+1, MPI_CHAR, source, tagContent, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			system("mkdir receive");
			//write to file
			f = fopen(directoryTemp,"w+");
			printf("--Save to %s\n", directoryTemp);
			
			fprintf(f, "%s", tempContent);	

			fclose(f);
			printf("--Receive successfuly\n");
			fflush(stdin);
		}
	}
	MPI_Finalize();
	return 0;
}