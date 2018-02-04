
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    FILE *f;
    int so;
    char *s;
    char filename[100];
    struct sockaddr_in ad;

    socklen_t ad_length = sizeof(ad);
    struct hostent *hep;

    // create socket
    int serv = socket(AF_INET, SOCK_STREAM, 0);

    // init address
    hep = gethostbyname(argv[1]);
    memset(&ad, 0, sizeof(ad));
    ad.sin_family = AF_INET;
    ad.sin_addr = *(struct in_addr *)hep->h_addr_list[0];
    ad.sin_port = htons(12345);

    // connect to server
    
    int temp=0;
	// after connected, it's client turn to chat
	int c;
	// send some data to server
	printf("client>");
	scanf("%s", filename);
	//open file to read using filename
    f = fopen(filename,"r");

    //get the length of file's content + filename
    size_t pos = ftell(f);    // Current position
	fseek(f, 0, SEEK_END);    // Go to end
	size_t length = ftell(f); // read the position which is the size
	fseek(f, pos, SEEK_SET);
	int lengthint = length+strlen(filename);

	//allocate data into string
 	s = (char *) malloc(lengthint*sizeof(char));
	//copy filename to the first part of s
	strcpy(s,filename);
	//append a new line in s
    strcat(s,"\n");
    //index for s, with value of filename
	temp = strlen(filename)+1;
	//save content of file into s
	if (f){
		while((c = getc(f))!=EOF)
			s[temp++] = c;
	}

	fclose(f);
	connect(serv, (struct sockaddr *)&ad, ad_length);
	write(serv, s, strlen(s) + 1);
	printf("send successfuly\n");
	// then it's server turn
    
}

