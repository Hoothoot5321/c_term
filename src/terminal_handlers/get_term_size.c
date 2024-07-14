#include "get_term_size.h"
#include "../structs/dimensions.h"
#include <windows.h>

int getTermSize(BoxDimension *term_size) {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  int columns, rows;

  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

  term_size->width = columns;

  term_size->height = rows;

  return 1;
}
