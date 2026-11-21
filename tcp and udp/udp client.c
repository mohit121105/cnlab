
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    char buffer[1024];

    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    char msg[] = "Hello from UDP Client";

    sendto(sock, msg, strlen(msg) + 1, 0,
           (struct sockaddr*)&server, len);

    recvfrom(sock, buffer, sizeof(buffer), 0,
             (struct sockaddr*)&server, &len);

    printf("Server says: %s\n", buffer);

    close(sock);

    return 0;
}
