#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void process_files(bool, bool, bool, const char*);
void process_blocks(bool, bool, bool);
#define PRINT(b,f,n) do {if (b) printf(f, n); } while(0)

int main(int argc, char* argv[]) {
  bool count_byte = false;
  bool count_word = false;
  bool count_line = false;
  bool file_present = false;
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
      switch (key[0]) {
        case 'c': count_byte = true; break;
        case 'l': count_line = true; break;
        case 'w': count_word = true; break;
        default: break;
      }
      printf("Short %s:%s\n", key, val);
    }
    else {
      if (!count_byte && !count_line && !count_word) {
        count_byte = count_line = count_word = true;
      }
      process_files(count_byte, count_line, count_word, argv[i]);
      file_present = true;
    }
  }
  if (!file_present) {
    if (!count_byte && !count_line && !count_word) {
      count_byte = count_line = count_word = true;
    }
    process_blocks(count_byte, count_line, count_word);
  }
  return 0;
}
void process_blocks( bool count_byte, bool count_line, bool count_word ) {
  size_t len = 0, read, bytes = 0, words = 0, lines = 0;
  char buffer[256];
  char prev = ' ';
  while (fgets(buffer, sizeof(buffer), stdin)!=NULL) {
    len = strlen(buffer);
    bytes += len; 
    size_t word_line = 0;
    for(int i = 0; i<len; ++i) {
      if (buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\r') {
        if (prev == ' ' || prev == '\n' || prev == '\r') {
          ++word_line;
        }
      }
      else if (buffer[i] == '\n') {
        ++lines;
      }
      prev = buffer[i];
    }
    words += word_line;
  }
  PRINT(count_line, "\t%zu", lines);
  PRINT(count_word, "\t%zu", words);
  PRINT(count_byte, "\t%zu", bytes);
  printf("\n");
}

void process_files( bool count_byte, bool count_line, bool count_word, const char* file ) {
  size_t len = 0, read, bytes = 0, words = 0, lines = 0;
  FILE* f = fopen(file, "r");
  if (f == NULL) {
    perror("error: opening file");
    return;
  }
  char* line = NULL;
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
  PRINT(count_line, "%zu", lines);
  PRINT(count_word, "%zu", words);
  PRINT(count_byte, "%zu", bytes);
  printf(" %s\n", file);
  free(line);
  fclose(f);
}
