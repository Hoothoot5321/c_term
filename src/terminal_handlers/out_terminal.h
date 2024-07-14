#ifndef OUT_TERMINAL_H_
#define OUT_TERMINAL_H_

#include <stddef.h>

#include "../structs/box_cords.h"

#include "../enums/states.h"

int outTerminalCenter(char *complete_out, size_t complete_size, char *out_str,
                      int term_width, char *i_bg_col, char *i_text_col);

int outTerminalLeft(char *complete_out, size_t complete_size, char *out_str,
                    int offset, char *i_bg_col, char *i_text_col);

int outTerminalLineCount(char *complete_out, size_t complete_size,
                         int line_count, int offset, char *i_bg_col,
                         char *i_line_num_col);

int outFileContent(char (*file_content)[1024], char *file_name, int line_count,
                   char *dividing_line, size_t complete_size,
                   BoxCords *mouse_cursor, char *i_bg_col, char *i_text_col,
                   char *i_line_num_col, WriteMode *write_mode);

#endif
