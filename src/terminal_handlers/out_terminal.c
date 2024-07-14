#include "out_terminal.h"
#include "../globals/colors.h"
#include "../globals/terminal_setting.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int outTerminalCenter(char *complete_out, size_t complete_size, char *out_str,
                      int term_width, char *i_bg_col, char *i_text_col) {
  int str_length = strlen(out_str);
  int start_pos = (term_width - str_length) / 2;
  char space_filler[start_pos + 1];
  for (int i = 0; i < start_pos; i++) {
    space_filler[i] = ' ';
  }
  space_filler[start_pos] = '\0';
  char temp_out[1024];
  sprintf(temp_out, "%s\e[K%s%s%s\e[0m", i_bg_col, space_filler, i_text_col,
          out_str);
  strcat_s(complete_out, complete_size, temp_out);
  return 0;
}

int outTerminalLeft(char *complete_out, size_t complete_size, char *out_str,
                    int offset, char *i_bg_col, char *i_text_col) {
  char space_filler[offset + 1];
  for (int i = 0; i < offset; i++) {
    space_filler[i] = ' ';
  }
  space_filler[offset] = '\0';
  char temp_out[1024];

  sprintf(temp_out, "%s\e[K%s%s%s", i_bg_col, space_filler, i_text_col,
          out_str);
  strcat_s(complete_out, complete_size, temp_out);
  return 0;
}

int outTerminalLineCount(char *complete_out, size_t complete_size,
                         int line_count, int offset, char *i_bg_col,
                         char *i_line_num_col) {

  int digits = floor(log10(abs(line_count))) + 1;

  char space_filler[offset - digits + 1];
  for (int i = 0; i < offset - digits; i++) {
    space_filler[i] = ' ';
  }
  space_filler[offset - digits] = '\0';
  char temp_out[1024];
  sprintf(temp_out, "%s\e[K%s%s%d", i_bg_col, space_filler, i_line_num_col,
          line_count);
  strcat_s(complete_out, complete_size, temp_out);

  return 0;
}

int outFileContent(char (*file_content)[1024], char *file_name, int line_count,
                   char *dividing_line, size_t complete_size,
                   BoxCords *mouse_cursor, char *i_bg_col, char *i_text_col,
                   char *i_line_num_col, WriteMode *write_mode) {

  char complete_out[complete_size];
  int running = 1;

  complete_out[0] = '\0';
  strcat_s(complete_out, complete_size, "\e[H");
  outTerminalCenter(complete_out, complete_size, file_name,
                    terminal_dimensions.width, i_bg_col, i_text_col);
  strcat_s(complete_out, complete_size, "\n");
  switch (*write_mode) {
  case NORMAL:
    outTerminalCenter(complete_out, complete_size, "Normal",
                      terminal_dimensions.width, normal_header_bg_col,
                      normal_header_text_col);
    break;
  case INSERT:
    outTerminalCenter(complete_out, complete_size, "Insert",
                      terminal_dimensions.width, insert_header_bg_col,
                      insert_header_text_col);
    break;
  }
  strcat_s(complete_out, complete_size, "\n");
  outTerminalLeft(complete_out, complete_size, dividing_line, 0, i_bg_col,
                  i_text_col);
  strcat_s(complete_out, complete_size, "\n");
  for (int i = 0; i < line_count; i++) {
    int line_num = i + 1;
    if (relative_lines) {
      if (i == mouse_cursor->y - min_y) {
        line_num = i + 1;
      } else if (i < mouse_cursor->y - min_y) {
        line_num = mouse_cursor->y - min_y - i;
      } else {
        line_num = i - mouse_cursor->y + min_y;
      }
    }
    outTerminalLineCount(complete_out, complete_size, line_num, min_x - 2,
                         i_bg_col, i_line_num_col);
    outTerminalLeft(complete_out, complete_size, file_content[i], 1, i_bg_col,
                    i_text_col);
  }
  for (int i = line_count + min_y; i < terminal_dimensions.height; i++) {
    strcat_s(complete_out, complete_size, "\e[K\n");
  }
  char temp[100];
  sprintf(temp, "\e[0m\e[%d;%dH", mouse_cursor->y, mouse_cursor->x);
  strcat_s(complete_out, complete_size, temp);
  fputs(complete_out, stdout);
  return 0;
}
