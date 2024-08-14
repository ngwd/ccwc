#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
  for(int i = 0; i<argc; ++i) {
    if (strncmp(argv[i], "--", 2) == 0) {
      printf("Long option %s\n", argv[i]);
    }
    else if (strncmp(argv[i], "-", 1) == 0) {
      printf("Short option %s\n", argv[i]);
    }
    else {
      printf("found arguments, argv[i]\n");
    }
  }
  return 0;
}