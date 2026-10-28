#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define BLUE "\e[1;34m"

void print_file(const char *name, int is_dir) {
  if (is_dir)
    printf("\e[1;34m%s\e[0m\n", name);
  else
    printf("%s\n", name);
}

int walk(const char *path) {
  DIR *dir = opendir(path);
  if (!dir) {
    perror("openir");
    return 1;
  }
  struct dirent *dp;
  while ((dp = readdir(dir)) != NULL) {
    const char *name = dp->d_name;
    // ignore files
    if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
      continue;
    }
    if (dp->d_type == DT_DIR) {
      print_file(name, 0);
    }
    //
    else {
      print_file(name, 1);
    }
  }
  closedir(dir);
  return 0;
}

int main(int argc, char **argv) {
  const char *path = ".";
  if (argc > 1)
    path = argv[1];
  int err = walk(path);
  return err;
}
