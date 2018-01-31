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
			int lengthContent = length;
			printf("%d\n", lengthContent);

			//allocate data into string
			char *content;
			content = (char *) malloc(lengthContent*sizeof(char));
			if (f){
            			while((c = getc(f))!=EOF)
                		content[temp++] = c;
        		}
        		//printf("%s\n", content);
			int count=0;
			int tempLengthContent= lengthContent;
			while(tempLengthContent!=0){
				tempLengthContent = tempLengthContent/10;
				count+=1;
			}
			printf("%d\n", count);
			fclose(f);
			int tem;
			//send using mpi
			MPI_Send(&lengthContent, count, MPI_INT, dest, tagContentSize, MPI_COMM_WORLD);
			tem = sizeof(lengthContent)/sizeof(int);
			printf("this is temp for lengthContent%d\n", tem);

			MPI_Send(fileName, sizeof(fileName)/sizeof(char), MPI_CHAR, dest, tagName, MPI_COMM_WORLD);
			tem = sizeof(fileName)/sizeof(char);
			printf("this is temp for filename%d\n", tem);

			MPI_Send(content, lengthContent, MPI_CHAR, dest, tagContent, MPI_COMM_WORLD);
			

			printf("Send successfuly\n");
			free(content);
		}else { //receive file 	
			printf("This is Receive\n");	

			char directoryTemp[] = "receive/";
			char fileName[100];
			
			//recv using mpi
			int lengthContent;
			
			//printf("first\n");
			//recv length of the contents
			MPI_Recv(&lengthContent, 100, MPI_INT, source, tagContentSize, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			//printf("This is lengthContent %d\n", lengthContent);

			//allocate for the contents of file
			char *tempContent;
			tempContent = (char *) malloc(sizeof(char)*lengthContent);
			
			//recving file content including name
			//printf("second\n");
			MPI_Recv(fileName, 100, MPI_CHAR, source, tagName, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			//printf("This is fileName %s\n", fileName);

			strcat(directoryTemp,fileName);
			//printf("third\n");
			MPI_Recv(tempContent, lengthContent+1, MPI_CHAR, source, tagContent, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			system("mkdir receive");
			//write to file
			f = fopen(directoryTemp,"w+");
			printf("--Save to %s\n", directoryTemp);
			
			fprintf(f, "%s", tempContent);	

			fclose(f);
			printf("--Receive successfuly\n");
			free(tempContent);
			fflush(stdin);
		}
	}
	MPI_Finalize();
	return 0;
}
