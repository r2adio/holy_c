#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define IP_ADDRESS "127.0.0.1" // IP address to listen on
#define PORT 42069             // Port number to listen on

int main() {
  // creates a socket
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    perror("Failed to create socket");
    return EXIT_FAILURE;
  }

  // binds an add and port to the socket
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(IP_ADDRESS);
  address.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("Failed to bind socket");
    return 1;
  }

  // listen for incoming connections
  // limits the number of incoming connections to 3
  listen(server_fd, 3);

  printf("Server is running and listening on port %d...\n", PORT);

  while (1) {
    // accept an incoming connection
    int addrlen = sizeof(address);
    // accept() does the three-way handshake
    int new_socket =
        accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

    if (new_socket < 0) {
      perror("Failed to accept connection");
      continue;
    }

    printf("Connection accepted.\n");

    char buffer[4096];
    ssize_t bytes_read = read(new_socket, buffer, sizeof(buffer) - 1);
    if (bytes_read <= 0) {
      close(new_socket);
      continue;
    }

    buffer[bytes_read] = '\0';
    printf("Client message: %s\n", buffer);

    // Respond to the client
    char response[4096];
    snprintf(response, sizeof(response), "Server received your message: %s",
             buffer);
    write(new_socket, response, strlen(response)); // send response to client

    // four-way handshake
    close(new_socket);
    printf("Connection closed.\n");
  }

  // close the listening socket
  close(server_fd);
  return EXIT_SUCCESS;
}
