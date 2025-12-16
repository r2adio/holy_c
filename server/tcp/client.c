#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 42069
#define BUFFER_SIZE 4096

int main() {
  int sock = 0;
  struct sockaddr_in serv_addr;
  char buffer[BUFFER_SIZE] = {0};
  const char *client_msg = "this is a message from client";

  // create socket file descriptor
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  // convert IPv4 and IPv6 addresses from text to binary form
  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
    perror("Invalid address/ Address not supported");
    exit(EXIT_FAILURE);
  }

  // connect to the server
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("Connection Failed");
    exit(EXIT_FAILURE);
  }

  printf("Connected to server on port %d\n", PORT);

  send(sock, client_msg, strlen(client_msg), 0);
  printf("Client: %s message sent\n", client_msg);

  ssize_t valread = recv(sock, buffer, BUFFER_SIZE - 1, 0);
  if (valread > 0) {
    printf("Server: %s\n", buffer);
  } else if (valread == 0) {
    printf("Server closed connection\n");
  } else {
    perror("recv failed");
  }

  close(sock);
  return 0;
}
