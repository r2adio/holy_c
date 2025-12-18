#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 42069
#define CONN_BACKLOG 3

#define LOG_INFO "\x1b[1;32mINFO: \x1b[0m"
#define LOG_ERROR "\x1b[1;31mERROR: \x1b[0m"

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    perror(LOG_ERROR "Failed to create socket");
    return EXIT_FAILURE;
  }

  // avoids `Address already in use` error
  int reuseaddr = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr,
                 sizeof(reuseaddr)) < 0) {
    perror(LOG_ERROR "Failed to set socket options");
    return EXIT_FAILURE;
  }

  struct sockaddr_in serv_addr = {
      .sin_family = AF_INET,
      .sin_port = htons(PORT),
      .sin_addr = {htonl(INADDR_ANY)},
  };

  if (bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    perror(LOG_ERROR "Failed to bind socket");
    return EXIT_FAILURE;
  }

  if (listen(server_fd, CONN_BACKLOG) < 0) {
    perror(LOG_ERROR "Failed to listen on socket");
    return EXIT_FAILURE;
  }

  fprintf(stderr, LOG_INFO "Server is running and listening on port %d...\n",
          PORT);

  while (1) {
    int client_fd;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
                            &client_addr_len)) < 0) {
      perror(LOG_ERROR "Failed to accept connection");
      return EXIT_FAILURE;
    }

    fprintf(stderr, LOG_INFO "Connection accepted.\n");

    // http response: status line + headers + body
    const char *resp = "HTTP/1.1 200 OK\r\n"
                       "Content-Type: text/plain; charset=utf-8\r\n"
                       "Content-Length: 12\r\n"
                       "Connection: close\r\n"
                       "\r\n"
                       "Hello World!";

    if (send(client_fd, resp, strlen(resp), 0) < 0) {
      perror(LOG_ERROR "Failed to send response");
      return EXIT_FAILURE;
    }
    fprintf(stderr, LOG_INFO "Response sent.\n");

    close(client_fd);
    fprintf(stderr, LOG_INFO "Connection closed.\n");
  }
  close(server_fd);
  fprintf(stderr, LOG_INFO "Server closed.\n");
  return EXIT_SUCCESS;
}
