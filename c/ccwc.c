#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void process_lines(const char*, bool, bool, bool);

int main(int argc, char* argv[]) {
  bool count_byte = false;
  bool count_word = false;
  bool count_line = false;
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
      printf("Short %s:%s\n", key, val);
      switch (key[0]) {
        case 'c': count_byte = true; break;
        case 'l': count_line = true; break;
        case 'w': count_word = true; break;
        default: break;
      }
    }
    else {
      if (!count_byte && !count_line && !count_word) {
        count_byte = count_line = count_word = true;
      }
      process_lines(argv[i], count_byte, count_line, count_word);
    }
  }

  return 0;
}
void process_lines(const char* file, bool count_byte, bool count_line, bool count_word) {
  FILE* f = fopen(file, "r");
  if (f == NULL) {
    perror("error: opening file");
    return;
  }
  char* line = NULL;
  size_t len = 0, read, bytes = 0, words = 0, lines = 0;
  while ((read = getline(&line, &len, f)) != -1) {
    ++lines;
    bytes += read;

    char prev = ' ';
    size_t word_line = 0;
    for(int i = 0; i<read; ++i) {
      if (line[i] != ' ' && prev == ' ') {
        ++word_line;
      }
      prev = line[i];
    }
    words += word_line;

  }
  if (count_line) {
    printf(" %ld", lines);
  }
  if (count_word) {
    printf(" %ld", words);
  }
  if (count_byte) {
    printf(" %ld", bytes);
  }
  printf(" %s\n", file);
  free(line);
  fclose(f);
}
