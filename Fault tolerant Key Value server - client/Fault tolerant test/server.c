#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <time.h>
#include <signal.h>
#include <netinet/in.h>

char s[100];
void* backing_up_thread(void *data){
    struct sockaddr_in ad1;

    socklen_t ad_length1 = sizeof(ad1);
    // create socket
    int serv = socket(AF_INET, SOCK_STREAM, 0);

    // init address
    memset(&ad1, 0, sizeof(ad1));
    ad1.sin_family = AF_INET;
    ad1.sin_port = htons(2412);
    ad1.sin_addr.s_addr = inet_addr("192.168.99.100");

    // connect to server
    connect(serv, (struct sockaddr *)&ad1, ad_length1);

    while (1) {
        // after connected, it's client turn to chat

        // send some data to server
        write(serv, s, strlen(s) + 1);

        // then it's server turn
        if(read(serv, s, sizeof(s))==0){
            printf("Backup server is down!");
            printf("\nRunning in non fault-tolerant mode...");
            pthread_detach(pthread_self());
        }
        else{
            printf("Successfully back up data");
        }
        break;
    }
}


int main() {
    int ss, cli, pid;
    struct sockaddr_in ad;
    socklen_t ad_length = sizeof(ad);
    pthread_t backup_thread;
    

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
            // I'm the son, I'll serve this client
        printf("Primary server ready.\n");
        printf("Client connected...\n");
        while (1) {
                // it's client turn to chat, I wait and read message from client
            read(cli, s, sizeof(s));
            printf("Client says: %s\n",s);
                // now it's my (server) turn
            pthread_create(&backup_thread, NULL, backing_up_thread, NULL); 
            pthread_join(backup_thread, NULL);
            printf("\nServer>");
            scanf("%s", s);
            write(cli, s, strlen(s) + 1);

        }
    }
    // disconnect
    close(cli);

}
