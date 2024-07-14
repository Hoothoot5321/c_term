#include "read_file.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int readFile(char (*file_content)[1024], const char *file_name,
             size_t line_capacity) {
  FILE *file;

  fopen_s(&file, file_name, "r");
  if (file == NULL) {
    printf("Could not open file: %s\n", file_name);
    return -1;
  }
  size_t line_count = 0;
  char line[1024];

  while (fgets(line, 1024, file) != NULL) {
    if (line_count == line_capacity) {
      line_capacity *= 2;
      char(*temp)[1024] =
          realloc(file_content, line_capacity * sizeof *file_content);
      if (temp == NULL) {
        printf("WTF\n");
        return 0;
      }
      file_content = temp;
    }
    strcpy_s(file_content[line_count], 1024, line);
    line_count++;
  }

  fclose(file);

  return line_count;
}
