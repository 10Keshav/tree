#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define BLUE "\e[1;34m"

void print_file(const char *name, int is_dir, int indent) {
  if (indent) {
    for (int i = 0; i < indent * 2; i++)
      printf("");
  }
  // printf("%*c", indent * 2, ' ');
  if (is_dir)
    printf(" \e[1;34m%s\e[0m\n", name);
  else
    printf(" %s\n", name);
}

int walk(const char *path, int indent) {
  DIR *dir = opendir(path);
  if (!dir) {
    perror("openir");
    return 1;
  }
  struct dirent *dp;
  while ((dp = readdir(dir)) != NULL) {
    const char *name = dp->d_name;
    // ignore files
    if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0 ||
        strcmp(name, ".git") == 0) {
      continue;
    }
    if (dp->d_type == DT_DIR) {
      print_file(name, 1, indent);
      // walk to sub path
      size_t len = strlen(path) + strlen(name) + 2;
      char sub_path[len];
      snprintf(sub_path, len, "%s/%s\n", path, name);
      walk(sub_path, indent + 1);
    }
    //
    else {
      print_file(name, 0, indent);
    }
  }
  closedir(dir);
  return 0;
}

int main(int argc, char **argv) {
  const char *path = ".";
  if (argc > 1)
    path = argv[1];
  int err = walk(path, 0);
  return err;
}
