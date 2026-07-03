#include <ctype.h>
#include <ncurses.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 1024
#define MAX_INPUT 256

const char *items[] = {"Firefox", "Ghostty",         "Zen",
                       "Safari",  "System Settings", "GIMP"};

int item_count = sizeof(items) / sizeof(items[0]);
int filtered[MAX_ITEMS];
int filtered_count;

char input[MAX_INPUT];

int contains_icase(const char *str, const char *needle) {
  if (*needle == '\0')
    return 1;
  size_t len = strlen(needle);

  for (; *str; str++) {
    size_t i;
    for (i = 0; i < len; i++) {
      if (!str[i])
        break;
      if (tolower((unsigned char)str[i] != tolower((unsigned char)needle[i])))
        break;
    }
    if (i == len)
      return 1;
  }
  return 0;
}

void update_filter(void) {
  filtered_count = 0;
  for (int i = 0; i < item_count; i++) {
    if (contains_icase(items[i], input))
      filtered[filtered_count++] = i;
  }
}

void draw(int selected) {
  erase();

  int prompt_len = strlen(input) + 10;
  int col = 0;
  int start_col = 0;

  if (selected >= filtered_count)
    selected = filtered_count - 1;
  if (selected < 0)
    selected = 0;

  mvprintw(0, 0, "> %s", input);

  col = prompt_len;

  int visible_start = 0;
  int total_width = 0;
  for (int i = 0; i < filtered_count; i++) {
    total_width += strlen(items[filtered[i]]) + 1;
  }

  if (total_width > COLS - prompt_len) {
    int needed = 0;
    for (int i = selected; i < filtered_count; i++) {
      needed += strlen(items[filtered[i]]) + 1;
    }
    if (needed < COLS - prompt_len) {
      visible_start = 0;
    } else {
      visible_start = selected;
    }
  }

  for (int i = visible_start; i < filtered_count; i++) {
    if (i == selected)
      attron(A_REVERSE);
    mvprintw(0, col, "%s", items[filtered[i]]);
    if (i == selected)
      attroff(A_REVERSE);
    col += strlen(items[filtered[i]]) + 1;
  }

  move(0, prompt_len + (selected - visible_start > 0
                            ? strlen(items[filtered[selected - 1]]) + 1
                            : 0));

  refresh();
}

int main(void) {
  input[0] = '\0';

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(1);

  update_filter();
  int selected = 0;
  while (1) {
    if (selected >= filtered_count)
      selected = filtered_count - 1;
    if (selected < 0)
      selected = 0;

    draw(selected);

    int ch = getch();
    switch (ch) {
    case KEY_LEFT:
      selected--;
      break;
    case KEY_RIGHT:
      selected++;
      break;
    case 10:
    case KEY_ENTER:
      endwin();
      if (filtered_count)
        printf("%s\n", items[filtered[selected]]);
      return 0;

    case KEY_BACKSPACE:
    case 127:
    case 8: {
      size_t len = strlen(input);
      if (len)
        input[len - 1] = '\0';
      update_filter();
      selected = 0;
      break;
    }
    case 'u' & 0x1f: {
      input[0] = '\0';
      update_filter();
      selected = 0;
      break;
    }
    case 'w' & 0x1f: {
      size_t len = strlen(input);
      while (len > 0 && input[len - 1] == ' ')
        input[--len] = '\0';
      while (len > 0 && input[len - 1] != ' ')
        input[--len] = '\0';
      update_filter();
      selected = 0;
      break;
    }
    default:
      if (isprint(ch)) {
        size_t len = strlen(input);
        if (len < MAX_INPUT - 1) {
          input[len] = ch;
          input[len + 1] = '\0';
          update_filter();
          selected = 0;
        }
      }
    }
  }
  endwin();
  return EXIT_SUCCESS;
}
