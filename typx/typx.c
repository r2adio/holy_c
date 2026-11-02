#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void read_input(char *buffer, size_t size) {
  if (fgets(buffer, size, stdin) == NULL) {
    buffer[0] = '\0';
    return;
  }

  buffer[strcspn(buffer, "\n")] = '\0';
}

static size_t count_correct_chars(const char *typed, const char *target) {
  size_t correct_chars = 0;

  for (size_t i = 0; typed[i] != '\0' && target[i] != '\0'; ++i) {
    if (typed[i] == target[i]) { ++correct_chars; }
  }

  return correct_chars;
}

static double elapsed_seconds(struct timespec start, struct timespec end) {
  return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

static double calculate_wpm(size_t char_count, double elapsed_sec) {
  if (elapsed_sec <= 0.0) { return 0.0; }

  return ((double)char_count / 5.0) * 60.0 / elapsed_sec;
}

static double calculate_accuracy(size_t correct_chars, size_t typed_len) {
  if (typed_len == 0) { return 0.0; }

  return ((double)correct_chars / (double)typed_len) * 100.0;
}

static void print_results(double raw_wpm, double net_wpm, double accuracy) {
  printf("WPM: %.2f (raw) %.2f (net)\n", raw_wpm, net_wpm);
  printf("Accuracy: %.2f %%\n", accuracy);
}

int main(void) {
  const char *target = "the quick brown fox jumps over the lazy dog";
  char input_buf[100];
  struct timespec start, end;

  printf("TYPE: %s\n", target);

  // avoid gettimeofday() -> a legacy code
  clock_gettime(CLOCK_MONOTONIC, &start); // good for benchmarking, runtime tracking
  read_input(input_buf, sizeof(input_buf));
  clock_gettime(CLOCK_MONOTONIC, &end);

  size_t typed_len = strlen(input_buf);
  size_t correct_chars = count_correct_chars(input_buf, target);
  double elapsed_sec = elapsed_seconds(start, end);
  double raw_wpm = calculate_wpm(typed_len, elapsed_sec);
  double net_wpm = calculate_wpm(correct_chars, elapsed_sec);
  double accuracy = calculate_accuracy(correct_chars, typed_len);

  print_results(raw_wpm, net_wpm, accuracy);
  return EXIT_SUCCESS;
}
