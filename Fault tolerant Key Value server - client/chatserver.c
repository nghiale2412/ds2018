#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define insert "insert"
#define get "get"
#define modify "modify"
#define delete "delete"

int main() {
    FILE *f;
    int ss, cli, pid, lengtChar,i,j;
    char lengthRead[10];
    
            
    struct sockaddr_in ad;
    socklen_t ad_length = sizeof(ad);

    // create the socket
    ss = socket(AF_INET, SOCK_STREAM, 0);

    // bind the socket to port 12345
    memset(&ad, 0, sizeof(ad));
    ad.sin_family = AF_INET;
    ad.sin_addr.s_addr = INADDR_ANY;
    ad.sin_port = htons(12345);
    bind(ss, (struct sockaddr *)&ad, ad_length);

    // then listen
    listen(ss, 0);

    while (1) {
        // an incoming connection
        cli = accept(ss, (struct sockaddr *)&ad, &ad_length);

        pid = fork();
        if (pid == 0) {
            // I'm the son, I'll serve this client
            printf("client connected\n");
            while (1) {
                // it's client turn to chat, I wait and read message from client
                printf("SERVER>\n");
                char commandTemp[10],keyTemp[150],valueTemp[100],s[1000];
                //initialize default value
                commandTemp[0]='\0';
                keyTemp[0]='\0';
                valueTemp[0]='\0';
                //default directory
                char directoryTemp[] = "receive/";
                //read data from client 
                read(cli, s, sizeof(s));
                printf("Command receive : %s\n", s);
                i=5;
                
                //read the command from data from data received
                for (j = 0; j < 10; ++j)
                {
                    if (s[i]=='<')
                    {
                        commandTemp[j]='\0';
                        i=i+11;
                        break;
                    }else{

                        commandTemp[j]=s[i];
                        i++;
                    }

                }

                //if according to command
                //insert
                if (strcmp(commandTemp,insert)==0)
                {
                    printf("insert\n");
                    //read key and value from data received
                    for (j = 0; j < 100; ++j)
                    {
                        if (s[i]=='<')
                        {
                            keyTemp[j]='\0';
                            i=i+13;
                            break;
                        }else{
                            printf("%d %c\n",i,s[i]);                            
                            keyTemp[j]=s[i];
                            i++;
                        }
                    }
                    for (j = 0; j < 150; ++j)
                    {
                        if (s[i]=='<')
                        {
                            valueTemp[j]='\0';
                            break;
                        }else{
                            printf("%d %c\n",i,s[i]);
                            valueTemp[j]=s[i];
                            i++;
                        }
                    }


                    //check exist folder if not make dir
                    if (access(directoryTemp, F_OK) == -1)
                    {
                        system("mkdir receive");

                    }
                    
                    //access according to key
                    strcat(directoryTemp,keyTemp);
                    if (access(directoryTemp,F_OK) != -1)
                    {
                        //write send to client
                        printf("%s is already initialized (modify instead of insert)\n", keyTemp);
                        char temp[] = "already initialized";
                        write(cli, temp, strlen(temp)+1);
                    }else{
                        //create new file
                        f = fopen(directoryTemp, "w+");
                        fprintf(f,"%s", valueTemp);
                        fclose(f);
                        char temp[] = "\0";
                        write(cli, temp, strlen(temp)+1);
                    }
                        
                //modify
                }else if (strcmp(commandTemp,modify)==0)
                {
                    printf("modify\n");
                    //read key and value
                    for (j = 0; j < 100; ++j)
                    {
                        if (s[i]=='<')
                        {
                            keyTemp[j]='\0';
                            i=i+13;
                            break;
                        }else{
                            keyTemp[j]=s[i];
                            i++;
                        }
                    }
                    for (j = 0; j < 150; ++j)
                    {
                        if (s[i]=='<')
                        {
                            valueTemp[j]='\0';
                            break;
                        }else{
                            valueTemp[j]=s[i];
                            i++;
                        }
                    }
                    strcat(directoryTemp,keyTemp);

                    //check exist file
                    if( access( directoryTemp, F_OK ) != -1 ) {
                        //modify content of the file
                        f = fopen(directoryTemp, "w+");
                        fprintf(f, "%s", valueTemp);  
                        fclose(f);
                        char temp[] = "\0";
                        write(cli, temp, strlen(temp)+1);
                    } else {
                        //write send to client
                        printf("%s is not initialized\n", keyTemp);
                        char temp[] = "not initialized";
                        write(cli, temp, strlen(temp)+1);
                    }

                //get command
                }else if (strcmp(commandTemp,get)==0)
                {
                    //read key
                    for (j = 0; j < 100; ++j)
                    {
                        if (s[i]=='<')
                        {
                            keyTemp[j]='\0';
                            break;
                        }else{
                            keyTemp[j]=s[i];
                            i++;
                        }
                    }
                    printf("get\n");
                    strcat(directoryTemp,keyTemp);
                    //check exist file
                    if( access( directoryTemp, F_OK ) != -1 ) {
                        f = fopen(directoryTemp, "r");
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
                        fread(content, length, 1, f);  
                        fclose(f);
                        //send back content to client
                        write(cli, content, strlen(content)+1);
                        free(content);
                    } else {
                        //write send to client
                        printf("%s is not initialized\n", keyTemp);
                        char temp[] = "not initialized";
                        write(cli, temp, strlen(temp)+1);
                    }

                //delete command
                }else if (strcmp(commandTemp,delete)==0)
                {
                    //read key
                    for (j = 0; j < 100; ++j)
                    {
                        if (s[i]=='<')
                        {
                            keyTemp[j]='\0';
                            break;
                        }else{
                            keyTemp[j]=s[i];
                            i++;
                        }
                    }
                    printf("delete\n");
                    strcat(directoryTemp,keyTemp);

                    //check exist file
                    if( access( directoryTemp, F_OK ) != -1 ) {
                        //remove file return int 0, 1
                        int ret = remove(directoryTemp);
                        char temp[] = "\0";
                        write(cli, temp, strlen(temp)+1);
                    } else {
                        //write send to client
                        printf("%s is not defined\n", keyTemp);
                        char temp[] = "not defined";
                        write(cli, temp, strlen(temp)+1);
                    }
                }
                printf("%s\n", keyTemp);
                printf("%s\n", valueTemp);
                printf("End\n");
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
