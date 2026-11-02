#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void) {
  char *str = "the quick brown fox jumps over the lazy dog";
  printf("TYPE: %s\n", str);
  char input_buf[100];
  struct timespec start, end;

  // avoid gettimeofday() -> a legacy code
  clock_gettime(CLOCK_MONOTONIC, &start);     // good for benchmarking, runtime tracking
  fgets(input_buf, sizeof(input_buf), stdin); // read stops after eof or \n
  clock_gettime(CLOCK_MONOTONIC, &end);
  input_buf[strcspn(input_buf, "\n")] = '\0';

  double elapsed_sec = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
  double wpm = ((double)strlen(input_buf) / 5) * 60.0 / elapsed_sec;
  printf("WPM: %.2f\n", wpm);
  return EXIT_SUCCESS;
}
