
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    char buffer[1024];

    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr*)&server, sizeof(server));

    printf("UDP Server waiting for message...\n");

    recvfrom(sock, buffer, sizeof(buffer), 0,
             (struct sockaddr*)&client, &len);

    printf("Client says: %s\n", buffer);

    char msg[] = "Hello from UDP Server";

    sendto(sock, msg, strlen(msg) + 1, 0,
           (struct sockaddr*)&client, len);

    close(sock);

    return 0;
}
