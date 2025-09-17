/* display_screen.c:
 *  clears the screen and prints a sample object
 *  then waits for 100,000 microseconds (0.1 seconds)
 *  then clears the screen and repeats
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  // printf("start:");
  int8_t frame = 0;
  const char *obj = " ї\n"
                    "ΞΞΞ\n";
  char *spaces = "  ";

  while (1) {
    printf("THE GAME HAS BEGUN\n");
    printf("%s", obj);
    frame++;

    // time b/w each frame
    usleep(100000); // 100,000 microseconds (0.1 seconds)
    system("clear");

    // how many frames should run
    if (frame == 10) {
      break;
    }
  }

  return EXIT_SUCCESS;
}
