
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <signal.h>
#include <netinet/in.h>

struct sockaddr_in ad;
void server_status_check(int sock);
void tcp_connect();

int main(int argc, char* argv[]) {
    struct hostent *hep;
    // init address
    hep = gethostbyname(argv[1]);
    memset(&ad, 0, sizeof(ad));
    ad.sin_family = AF_INET;
    ad.sin_addr = *(struct in_addr *)hep->h_addr_list[0];
    ad.sin_port = htons(12345);
    tcp_connect();

}

void tcp_connect(){
    char s[100];
    socklen_t ad_length = sizeof(ad);
    int serv = socket(AF_INET, SOCK_STREAM, 0);
    // connect to server
    connect(serv, (struct sockaddr *)&ad, ad_length);
    while (1) {
        // after connected, it's client turn to chat
        // send some data to server
        //server_status_check(serv);
        printf("Client>");
        scanf("%s", s);
        write(serv, s, strlen(s) + 1);

        // then it's server turn
        if(read(serv, s, sizeof(s)) == 0){
            printf("Server crashed\n");
            printf("Using backup service...");
            close(serv);
            ad.sin_port = htons(2412);
            ad.sin_addr.s_addr = inet_addr("192.168.99.100");
            tcp_connect();
        }
        else{
            printf("Action performed successfully!");
        } 
    }
}



/*void server_status_check(int sock){
    char hb[]="hb";
    //send packet to server
    if (send(sock, &hb, sizeof(hb),0)<0)
        printf("Error sending\n");
    //if packet is received from server
    if((recv(sock, &hb, sizeof(hb),0)>0))
    {
        printf("Server responded\n");

    }
    else {
        
    }
}*/

