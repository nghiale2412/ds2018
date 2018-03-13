#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

typedef struct keyvalues{
    char* key;
    char* value;
}keyvalue;

// void delete(char* key){

// }

// node get(char* key){

// }

// void set(char* key, char* value){

// }


int main(int argc, char* argv[]) {
    int so,j,i;
    char s[100];
    struct sockaddr_in ad;

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
        // after connected, it's client turn to chat
        int i=0,j;        
        // send some data to server
        printf("client> ");
        scanf("%[^\n]%*c",s);
        while(s[0]==' '){
            for (i = 0; i < strlen(s); i++)
            {
                s[i]=s[i+1];
            }
        }
        int n = strlen(s);
        i=0;
        while(i<n)
        {
            if(s[i]==' ' && (s[i+1]==' ' || s[i-1]==' '))
            {
                for(j=i;j<n;j++)
                s[j]=s[j+1];
                n--;
            }
            else
            {
                i++;
            }
        }
        printf("%s\n",s);
        int count =0,count2=0,count3=0;
        for (i = 0; i < strlen(s); i++)
        {
            if (s[i]==' '){
                i++;
                break;
            }
            count++;
        }
        char *para1;
        para1 = (char *) malloc(sizeof(char) *(count));
        printf("%d\n", count);
        int index = 0;
        for (j = 0; j < count; j++)
        {
            printf("%c\n", s[j]);
            para1[index] = s[j];
            index++;
        }
        //
        for (; i < strlen(s); i++)
        {
            if (s[i]==' ')
            {
                i++;
                break;
            }
            count2++;
        }
        char *para2;
        para2 = (char *) malloc(sizeof(char)*(count2));
        printf("%d\n", count2);
        index =0;
        int temp = j+1+count2;
        for (j = j+1; j < temp; j++)
        {
            printf("%c\n", s[j]);
            para2[index] = s[j];
            index++;
        }

        //
        for (; i < strlen(s); i++)
        {
            if (s[i]==' ')
            {
                i++;
                break;
            }
            count3++;
        }
        char *para3;
        para3 = (char *) malloc(sizeof(char)*(count3));
        temp = j+1+count3;
        printf("%d\n", count3);
        index=0;
        for (j = j+1; j < temp; j++)
        {
            printf("%c\n", s[j]);
            para3[index] = s[j];
            index++;
        }
        printf("%s\n", para1);
        printf("%s\n", para2);
        printf("%s\n", para3);
        
        write(serv, s, strlen(s) + 1);

        // then it's server turn
    }
}

