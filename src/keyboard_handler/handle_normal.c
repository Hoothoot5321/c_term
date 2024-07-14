

#include "handle_normal.h"
#include "../globals/terminal_setting.h"
#include <string.h>
int handle_normal(char key, BoxCords *mouse_cords, BoxCords *real_mouse_cords,
                  WriteMode *write_mode, int *running,
                  char (*file_content)[1024], int *line_count) {
  switch (key) {
  case 'q':
    *running = 0;
    break;
  case 'k':
    if (mouse_cords->y - 1 >= min_y) {
      if (real_mouse_cords->x >
          strlen(file_content[mouse_cords->y - min_y - 1]) + min_x - 1) {
        mouse_cords->x =
            strlen(file_content[mouse_cords->y - min_y - 1]) + min_x - 1;
      } else {
        mouse_cords->x = real_mouse_cords->x;
      }
      mouse_cords->y -= 1;
      real_mouse_cords->y = mouse_cords->y;
    }
    break;

  case 'h':
    if (mouse_cords->x - 1 >= min_x) {
      mouse_cords->x -= 1;
      real_mouse_cords->x = mouse_cords->x;
    }
    break;

  case 'l':
    if (mouse_cords->x + 1 <=
        strlen(file_content[mouse_cords->y - min_y]) + min_x - 1) {
      mouse_cords->x += 1;
      real_mouse_cords->x = mouse_cords->x;
    }
    break;

  case 'j':
    if (mouse_cords->y + 1 < *line_count + min_y) {
      if (real_mouse_cords->x >
          strlen(file_content[mouse_cords->y - min_y + 1]) + min_x - 1) {
        mouse_cords->x =
            strlen(file_content[mouse_cords->y - min_y + 1]) + min_x - 1;
      } else {
        mouse_cords->x = real_mouse_cords->x;
      }
      mouse_cords->y += 1;
      real_mouse_cords->y = mouse_cords->y;
    }
    break;
  case 'x':
    file_content[mouse_cords->y - min_y][mouse_cords->x - min_x] = 'x';
    break;
  case 'i':
    *write_mode = INSERT;
    break;
  }
  return 1;
}
