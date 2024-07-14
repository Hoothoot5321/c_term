#include "enums/states.h"
#include "file_handlers/read_file.h"
#include "globals/colors.h"
#include "globals/settings.h"
#include "globals/terminal_setting.h"

#include "keyboard_handler/handle_insert.h"
#include "keyboard_handler/handle_normal.h"
#include "structs/box_cords.h"
#include "structs/dimensions.h"
#include "terminal_handlers/out_terminal.h"
#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>

#include <conio.h>
#include <stddef.h>

int main(int argc, char *argv[]) {
  if (argc < 1) {
    printf("Too few arguments\n");
    return 1;
  }

  char *file_name = argv[1];

  if (setupSettings() == -1) {
    printf("Failed loading settings");
    return 1;
  };

  char dividing_line[terminal_dimensions.width];
  dividing_line[0] = '#';
  for (int i = 1; i < terminal_dimensions.width - 2; i++) {
    dividing_line[i] = '-';
  }
  dividing_line[terminal_dimensions.width - 2] = '#';
  dividing_line[terminal_dimensions.width - 1] = '\0';

  size_t line_capacity = 256;
  char(*file_content)[1024] = malloc(line_capacity * sizeof(*file_content));

  int line_count = readFile(file_content, file_name, line_capacity);

  if (line_count == -1) {
    printf("Error reading file\n");
    return 1;
  }
  size_t complete_size = line_count * sizeof(*file_content);
  char complete_out[complete_size];
  int running = 1;

  BoxCords base_cursor;
  base_cursor.x = min_x;
  base_cursor.y = min_y;

  BoxCords real_cursor;
  real_cursor.x = min_x;
  real_cursor.y = min_y;

  WriteMode write_mode = NORMAL;

  printf("\e[2J");
  outFileContent(file_content, file_name, line_count, dividing_line,
                 complete_size, &base_cursor, bg_col, text_col, line_num_col,
                 &write_mode);
  char pre = ' ';
  while (running) {
    if (_kbhit() != 0) {
      char key = _getch();
      if (write_mode == NORMAL) {
        handle_normal(key, &base_cursor, &real_cursor, &write_mode, &running,
                      file_content, &line_count);
      } else if (write_mode == INSERT) {
        handle_insert(key, &base_cursor, &real_cursor, &write_mode, &running,
                      file_content, &line_count);
      }
      outFileContent(file_content, file_name, line_count, dividing_line,
                     complete_size, &base_cursor, bg_col, text_col,
                     line_num_col, &write_mode);
    }
  }
  printf("\e[2J\e[H");
  return 0;
}
