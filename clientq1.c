#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd; 
    struct sockaddr_in saddress;
    char b[300];
    int num; 

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("Error opening socket");

    saddress.sin_family = AF_INET;
    saddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddress.sin_port = htons(8080);

    if (connect(sockfd, (struct sockaddr *) &saddress, sizeof(saddress)) < 0)
        error("Error connecting");

    bzero(b, sizeof(b));
    num = read(sockfd, b, sizeof(b)-1);
    if (num < 0) 
        error("Error reading from socket");
        
    //Output
    printf("Random number: %s\num", b);

    close(sockfd);
    return 0;
}