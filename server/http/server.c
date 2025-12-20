#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 42069
#define CONN_BACKLOG 3

#define LOG_INFO "\x1b[1;32mINFO: \x1b[0m"
#define LOG_ERROR "\x1b[1;31mERROR: \x1b[0m"

int server_fd = -1;
volatile sig_atomic_t kr = 1;
void handle_signal(int sig) {
  (void)sig;
  kr = 0;

  if (server_fd != -1) {
    close(server_fd); // async-signal-safe
    server_fd = -1;
  }
}

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  struct sigaction sa = {0};
  sa.sa_handler = handle_signal;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(SIGINT, &sa, NULL);

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
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

  while (kr) {
    int client_fd;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
                            &client_addr_len)) < 0) {
      if (!kr)
        break;
      perror(LOG_ERROR "Failed to accept connection");
      continue;
    }

    fprintf(stderr, LOG_INFO "Connection accepted.\n");

    // extract url path:
    char request[4096];
    ssize_t request_len = recv(client_fd, request, sizeof(request) - 1, 0);
    if (request_len < 0) {
      perror(LOG_ERROR "Failed to receive request");
      return EXIT_FAILURE;
    }
    request[request_len] = '\0';
    // fprintf(stderr, LOG_INFO "Request received: %s\n", request);

    // parse request
    char method[8], path[1024], version[16];
    if (sscanf(request, "%7[^ ] %1023[^ ] %15[^\r\n]", method, path, version) !=
        3) {
      fprintf(stderr, LOG_ERROR "Failed to parse request");
      return EXIT_FAILURE;
    }
    if (strstr(path, "..") != NULL) {
      fprintf(stderr, LOG_ERROR "Path traversal detected");
      return EXIT_FAILURE;
    }
    fprintf(stderr, LOG_INFO "Method: %s, Path: %s, Version: %s\n", method,
            path, version);
    if (strcmp(path, "/") == 0) { // 200 ok
      const char *resp_body = "Hello World!";
      char resp[256];
      snprintf(resp, sizeof(resp),
               "HTTP/1.1 200 OK\r\n"
               "Content-Type: text/plain; charset=utf-8\r\n"
               "Content-Length: %zu\r\n"
               "Connection: close\r\n"
               "\r\n"
               "%s",
               strlen(resp_body), resp_body);
      if (send(client_fd, resp, strlen(resp), 0) < 0) {
        perror(LOG_ERROR "Failed to send response");
        return EXIT_FAILURE;
      }
      fprintf(stderr, LOG_INFO "Response sent.\n");
    } else { // 404 not found
      char resp[256];
      const char *resp_body = "Not Found";
      snprintf(resp, sizeof(resp),
               "HTTP/1.1 404 Not Found\r\n"
               "Content-Type: text/plain; charset=utf-8\r\n"
               "Content-Length: %zu\r\n"
               "Connection: close\r\n"
               "\r\n"
               "%s",
               strlen(resp_body), resp_body);
      if (send(client_fd, resp, strlen(resp), 0) < 0) {
        perror(LOG_ERROR "Failed to send response");
        return EXIT_FAILURE;
      }
      fprintf(stderr, LOG_INFO "Response sent.\n");
    }

    // http response: status line + headers + body
    char resp[256];
    const char *resp_body = "Hello World!";
    snprintf(resp, sizeof(resp),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/plain; charset=utf-8\r\n"
             "Content-Length: %zu\r\n"
             "Connection: close\r\n"
             "\r\n"
             "%s",
             strlen(resp_body), resp_body);

    if (send(client_fd, resp, strlen(resp), 0) < 0) {
      perror(LOG_ERROR "Failed to send response");
      return EXIT_FAILURE;
    }
    fprintf(stderr, LOG_INFO "Response sent.\n");

    close(client_fd);
    fprintf(stderr, LOG_INFO "Connection closed.\n\n");
  }
  close(server_fd);
  fprintf(stderr, "\n" LOG_INFO "Server closed.\n");
  return EXIT_SUCCESS;
}
