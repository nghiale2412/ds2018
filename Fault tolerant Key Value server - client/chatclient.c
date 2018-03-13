#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

// typedef struct keyvalues{
//     char* key;
//     char* value;
// }keyvalue;

#define insertCommand "<CMD>insert</CMD>"
#define modifyCommand "<CMD>modify</CMD>"
#define getCommand "<CMD>get</CMD>"
#define deleteCommand "<CMD>delete</CMD>"

char *inputString(FILE* fp, size_t size){
//The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(char)*size);//size is start size
    if(!str)return str;

    //read until end of stdin
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(char)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(char)*len);
}

// void delete(char* key){

// }

// node get(char* key){

// }

// void set(char* key, char* value){

// }

//add string with specific key
char *strcatMutiplyK(char *s, char *key){
    strcat(s,"<key>");
    strcat(s,key);
    strcat(s,"</key>");
    return s;
}

//add string with key and value
char *strcatMutiplyKV(char *s,char *key,char *value){
    strcatMutiplyK(s,key);
    strcat(s,"<value>");
    strcat(s,value);
    strcat(s,"</value>");
    return s;
}

int main(int argc, char* argv[]) {
    int so,j,i;
    char *s;
    char *tempError;
    struct sockaddr_in ad;
    printf("\n");
    socklen_t ad_length = sizeof(ad);
    struct hostent *hep;

    // create socket
    int serv = socket(AF_INET, SOCK_STREAM, 0);

    // init address
    //hep = gethostbyname(argv[1]);
    hep = gethostbyname("localhost");
    memset(&ad, 0, sizeof(ad));
    ad.sin_family = AF_INET;
    ad.sin_addr = *(struct in_addr *)hep->h_addr_list[0];
    ad.sin_port = htons(12345);

    // connect to server
    connect(serv, (struct sockaddr *)&ad, ad_length);
    while (1) {

        char *keyTemp,*valueTemp;        
        // after connected, it's client turn to chat
        int i=0,j,length;
        char lengthChar[100];
        // send some data to server
        char choose = ' ';
        while(choose!=5){
            printf("CLIENT> \n");
            printf("  1. Insert\n");
            printf("  2. Modify\n");
            printf("  3. Delete\n");
            printf("  4. Get\n");
            printf("  5. Quit\n");
            printf("  Choose : ");
            scanf("%c",&choose);
            switch(choose){
                //insert
                case '1':
                    s=NULL;
                    printf("INSERT \n");
                    //prevent new line
                    tempError = inputString(stdin,10);
                    printf("Enter Key : \n");
                    //dynamics input for key
                    keyTemp = inputString(stdin,10);
                    printf("Enter Value : \n");
                    //dynamics input for value
                    valueTemp = inputString(stdin,10);
                    s = (char *) malloc(sizeof(char)*(strlen(keyTemp)+strlen(valueTemp)+50));
                    //strcat(s,insertCommand);
                    s[0] = '\0';
                    //add default command string
                    strcat(s,"<CMD>insert</CMD>");
                    strcatMutiplyKV(s,keyTemp,valueTemp);
                    //get length of string + terminate character
                    length = strlen(s)+1;
                    printf("%s\n", s);
                    //from int to string
                    sprintf(lengthChar, "%d", length);
                    // write(serv, lengthChar, 10);
                    //send data to server
                    write(serv, s, strlen(s));
                    
                    free(keyTemp);
                    free(valueTemp);
                    free(s);
                    read(serv, lengthChar, sizeof(lengthChar));
                    printf("%s\n", lengthChar);
                    break;
                //modify
                case '2':
                    printf("MODIFY\n");
                    tempError = inputString(stdin,10);
                    
                    printf("Enter Key : \n");
                    keyTemp = inputString(stdin,10);
                    printf("Enter Value : \n");
                    valueTemp = inputString(stdin,10);
                    s = (char *) malloc(sizeof(char)*(strlen(keyTemp)+strlen(valueTemp)+50));
                    // strcat(s,modifyCommand);
                    s[0] = '\0';
                    strcat(s,"<CMD>modify</CMD>");
                    strcatMutiplyKV(s,keyTemp,valueTemp);
                    length = strlen(s)+1;
                    sprintf(lengthChar, "%d", length);
                    // write(serv, lengthChar, strlen(lengthChar));
                    write(serv, s, length);
                    free(keyTemp);
                    free(valueTemp);
                    free(s);
                    read(serv, lengthChar, sizeof(lengthChar));
                    printf("%s\n", lengthChar);
                    break;
                //delete
                case '3':
                    printf("DELETE\n");
                    tempError = inputString(stdin,10);
                    printf("Enter Key : \n");
                    keyTemp = inputString(stdin,10);
                    s = (char *) malloc(sizeof(char)*(strlen(keyTemp)+50));
                    // strcat(s,deleteCommand);
                    s[0] = '\0';
                    strcat(s,"<CMD>delete</CMD>");
                    strcatMutiplyK(s,keyTemp);
                    length = strlen(s)+1;
                    sprintf(lengthChar, "%d", length);
                    // write(serv, lengthChar, strlen(lengthChar));
                    write(serv, s, length);
                    free(keyTemp);    
                    free(s);
                    read(serv, lengthChar, sizeof(lengthChar));
                    printf("%s\n", lengthChar);
                    break;
                //get
                case '4':
                    printf("GET\n");
                    tempError = inputString(stdin,10);
                    printf("Enter Key : \n");
                    keyTemp = inputString(stdin,10);
                    s = (char *) malloc(sizeof(char)*(strlen(keyTemp)+50));
                    // strcat(s,getCommand);
                    s[0] = '\0';
                    strcat(s,"<CMD>get</CMD>");
                    strcatMutiplyK(s,keyTemp);
                    sprintf(lengthChar, "%d", length);
                    // write(serv, lengthChar, strlen(lengthChar));
                    write(serv, s, length);
                    free(keyTemp);
                    free(s);
                    char tempContent[150];
                    read(serv, tempContent, sizeof(tempContent));
                    printf("%s\n", tempContent);
                    break;
                //quit
                case '5':
                    printf("QUIT\n");
                    break;
                default:
                    printf("Choose Again ....\n");

            }
        }
        if (choose==5)
        {
            break;
        }

        // then it's server turn
    }
}

