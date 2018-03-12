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

typedef struct lists{
    keyvalue kv;
    struct lists *next;   
}node;

typedef struct listDetail{
    int size;
    node *head;
}listdetail;

void init(listdetail *ld){
    ld->size = 0;
    ld->head = NULL;
}

node* initNode(keyvalue kvTemp){
    node* l = (node *) malloc(sizeof(node));
    l->kv = kvTemp;
    return l;
}

int isEmpty(listdetail *l){
    if (l->size == 0)
        return 1;
    else return 0;
}

void insert(node *listNew, listdetail *l){
    node *pTemp = l->head;
    int i = 0;
    int temp=0;
    for (i = 0; i < l->size; i++)
    {
        if (pTemp->kv.key == listNew->kv.key)
        {
            temp = 1;
        }
    }
    printf("%d\n", temp);

    listNew->next = l->head;
    l->head = listNew;
    l->size++;
}

void delete(){
}

node get(char* key, listdetail *ld){

}

void set(char* key, char* value){

}


int main(int argc, char* argv[]) {
    int so;
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
        
        // send some data to server
        printf("client> ");
        scanf("%s", s);

        write(serv, s, strlen(s) + 1);

        // then it's server turn
    }
}

