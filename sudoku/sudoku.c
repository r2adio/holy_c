// compilation cmd: gcc --std=c23 -Wall -Wextra sudoku.c && ./a.out <sudoku-string>
// eg: ./a.out "53..7....6..195....98....6.8...6...34..8.3..17...2...6.6....28....419..5....8..79"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE  9
#define EMPTY 0

void print_board(int board[SIZE][SIZE]);

int main(int argc, char **argv) {
  if (argc != 2) err(EXIT_FAILURE, "Usage: %s <sudoku>\n", argv[0]);
  char *input = argv[1];
  if (strlen(input) != 81) err(EXIT_FAILURE, "Error: Sudoku must contain exactly 81 characters.\n");

  int board[SIZE][SIZE];
  for (int i = 0; i < 81; i++) {
    int row = i / SIZE;
    int col = i % SIZE;
    if (input[i] == '.') board[row][col] = EMPTY;
    else if (input[i] >= '1' && input[i] <= '9') board[row][col] = input[i] - '0';
    else err(EXIT_FAILURE, "Error: Invalid character '%c' at position %d.\n", input[i], i);
  }
  print_board(board);
  return EXIT_SUCCESS;
}

void print_board(int board[SIZE][SIZE]) {
  for (int row = 0; row < SIZE; row++) {
    if (row == 3 || row == 6) printf("------+-------+------\n");
    for (int col = 0; col < SIZE; col++) {
      if (col == 3 || col == 6) printf("| ");
      if (board[row][col] == EMPTY) printf(". "); // replace 0 with .
      else printf("%d ", board[row][col]);
    }
    printf("\n");
  }
}
