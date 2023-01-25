#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd, new_sock;
    int random, num;
    struct sockaddr_in saddress, caddress; 
    char b[300]; 

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("Error opening socket");

    saddress.sin_family = AF_INET;
    saddress.sin_addr.s_addr = INADDR_ANY;
    saddress.sin_port = htons(8080);

    if (bind(sockfd, (struct sockaddr *) &saddress, sizeof(saddress)) < 0) 
        error("Error on binding");

    listen(sockfd, 5);
    socklen_t client_length = sizeof(caddress);
    new_sock = accept(sockfd, (struct sockaddr *) &caddress, &client_length);
    if (new_sock < 0) 
        error("Error on accept");

    //Generate number between 100 and 999 randomly
    srand(time(NULL));
    random = (rand() % 900) + 100;
    sprintf(b, "%d", random);

    num = write(new_sock, b, sizeof(b));
    if (num < 0) error("Error writing to socket");

    close(new_sock);
    close(sockfd);
    return 0;
}