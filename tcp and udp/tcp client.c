
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    char buffer[1024];

    struct sockaddr_in server;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr*)&server, sizeof(server));

    char msg[] = "Hello from TCP Client";
    send(sock, msg, strlen(msg) + 1, 0);

    recv(sock, buffer, sizeof(buffer), 0);

    printf("Server says: %s\n", buffer);

    close(sock);

    return 0;
}
