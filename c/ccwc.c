#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_lines(const char* file);
int main(int argc, char* argv[]) {
  char count_byte = 0;
  char count_word = 0;
  char* file = NULL;
  for(int i = 1; i<argc; ++i) {
    char* key = NULL;
    char* val = "";
    if (strncmp(argv[i], "--", 2) == 0) {
      key = &argv[i][2];
      if (i+1 < argc && argv[i+1][0] != '-') {
        val = argv[i+1]; 
        ++i; 
      }
      printf("Long %s:%s\n", key, val);
    }
    else if (strncmp(argv[i], "-", 1) == 0) { // short form of argument will not come with value 
      key = &argv[i][1];
      /*
      if (i+1 < argc && argv[i+1][0] != '-') {
        val = argv[i+1]; 
        ++i; 
      }
      */
      printf("Short %s:%s\n", key, val);
      switch (key[0]) {
        case 'c':
          count_byte = 1;
          break;
        default:
          break;
      }
    }
    else {
      printf("found arguments, %s\n", argv[i]);
      file = &argv[i];
    }
  }

  process_lines(file);
  return 0;
}
void process_lines(const char* file){
  FILE* f = fopen(file, "r");
  if (f == NULL) {
    perror("error: opening file");
    return;
  }
  char* line = NULL;
  size_t len = 0, read, byte_count = 0;
  while ((read = getline(&line, &len, f)) != -1) {
    printf("%c%c\n", line[read-2], line[read-1]);
    byte_count += read;
  }
  printf("byte count %ld\n", byte_count);
  free(line);
  fclose(f);
}