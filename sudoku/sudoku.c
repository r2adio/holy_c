#include "sudoku.h"

int main(int argc, char *argv[]) {
  int **puzzle;
  puzzle = createPuzzle();

  printPuzzle(puzzle);

  return 0;
}
