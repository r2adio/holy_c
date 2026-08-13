// compilation cmd: gcc -Wall -Wextra ls.c -o ls && ./ls
// note: recommends linux over mac, for expected results

#include <dirent.h>
#include <grp.h>
#include <linux/limits.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void mode_string(mode_t mode, char *str) {
  str[0] = '-';
  if (S_ISDIR(mode)) str[0] = 'd';
  if (S_ISLNK(mode)) str[0] = 'l';
  if (S_ISCHR(mode)) str[0] = 'c';
  if (S_ISBLK(mode)) str[0] = 'b';
  if (S_ISFIFO(mode)) str[0] = 'p';
  if (S_ISSOCK(mode)) str[0] = 's';

  str[1] = (mode & S_IRUSR) ? 'r' : '-';
  str[2] = (mode & S_IWUSR) ? 'w' : '-';
  str[3] = (mode & S_IXUSR) ? 'x' : '-';
  str[4] = (mode & S_IRGRP) ? 'r' : '-';
  str[5] = (mode & S_IWGRP) ? 'w' : '-';
  str[6] = (mode & S_IXGRP) ? 'x' : '-';
  str[7] = (mode & S_IROTH) ? 'r' : '-';
  str[8] = (mode & S_IWOTH) ? 'w' : '-';
  str[9] = (mode & S_IXOTH) ? 'x' : '-';
  str[10] = '\0';
}

void print_long(const char *dir, const char *name) {
  char fullPath[PATH_MAX]; // 1024->mac, 4096->linux
  snprintf(fullPath, sizeof(fullPath), "%s/%s", dir, name);

  struct stat st;
  if (lstat(fullPath, &st) < 0) {
    perror(name);
    return;
  }
  char modes[11]; // buffer for file permission string
  mode_string(st.st_mode, modes);

  struct passwd *pw = getpwuid(st.st_uid);
  struct group *gr = getgrgid(st.st_uid);
  const char *user = pw ? pw->pw_name : "?";
  const char *group = gr ? gr->gr_name : "?";

  char timebuf[64];
  struct tm *tm = localtime(&st.st_mtim.tv_sec); // use &st.st_mtimespec.tv_sec on mac
  strftime(timebuf, sizeof(timebuf), "%b %e %H:%M", tm);

  printf("%s %lu %s %s %ld %s %s\n", modes, (unsigned long)st.st_nlink, user, group,
      (long)st.st_size, timebuf, name);
}

int show_all = 0;
int long_fmt = 0;
int main(int argc, char **argv) {
  int opt;
  while ((opt = getopt(argc, argv, "al")) != -1) {
    switch (opt) {
      case 'a':
        show_all++;
        break;
      case 'l':
        long_fmt++;
        break;
      default:
        fprintf(stderr, "usage: %s [-al] [path]\n", argv[0]);
        return EXIT_FAILURE;
    }
  }

  const char *path = (optind < argc) ? argv[optind] : "."; // current dir
  DIR *dir = opendir(path);
  if (!dir) {
    perror("opendir");
    return EXIT_FAILURE;
  }
  struct dirent *entry;
  while ((entry = readdir(dir))) {
    if (!show_all && entry->d_name[0] == '.') continue; // avoid dotfiles without -a flag
    if (long_fmt) print_long(path, entry->d_name);
    else printf("%s\n", entry->d_name); // prints one entry at a time
  }
  closedir(dir); // call it on same dir stream as readdir()
  return EXIT_SUCCESS;
}
