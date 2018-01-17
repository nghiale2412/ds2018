#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main() {
    FILE *f;
    int ss, cli, pid, index;
    struct sockaddr_in ad;
    char s[1000];
    char directoryTemp[] = "receive/";
    socklen_t ad_length = sizeof(ad);
    char newline[] = "\n";
    // create the socket
    ss = socket(AF_INET, SOCK_STREAM, 0);

    // bind the socket to port 12345    
    memset(&ad, 0, sizeof(ad));
    ad.sin_family = AF_INET;
    ad.sin_addr.s_addr = INADDR_ANY;
    ad.sin_port = htons(12345);
    bind(ss, (struct sockaddr *)&ad, ad_length);

    // then listen
    printf("--This is server \n");
    listen(ss, 0);
    char tempFile[100];
    //system("mkdir receive");
    while (1) {
        // an incoming connection
        cli = accept(ss, (struct sockaddr *)&ad, &ad_length);
        pid = fork();
        if (pid == 0) {
            // I'm the son, I'll serve this client
            printf("--Client connected\n");
            while (1) {

                read(cli, s, sizeof(s));
                
                //get the file name and save in tempFile
                for (int i = 0; i < strlen(s); ++i)
                {
                    if(s[i]==newline[0]){
                        index = i;
                        break;
                    }else tempFile[i]=s[i];
                }
                printf("%s\n", tempFile);
                strcat(directoryTemp,tempFile);
                printf("--Save to %s\n", directoryTemp);
                //get content of the file
                char *tempContent;
                tempContent = (char *) malloc(sizeof(char)*strlen(s));
                int j=0;
                //+2 in index will prevent \n
                for (int i = index+1; i < strlen(s); ++i){
                    tempContent[j++]=s[i];                            
                }
                printf("--Content of the file : \n%s\n",tempContent);
                //open file with directory receive/<filename>
                f=fopen(directoryTemp,"w+");
                
                fprintf(f, "%s",tempContent);
                fflush(stdin);
                fclose(f);
                printf("--Receive successfuly\n");
                break;
            }
            return 0;
        }
        else {
            // I'm the father, continue the loop to accept more clients
            continue;
        }
    }
    // disconnect
    close(cli);

}
