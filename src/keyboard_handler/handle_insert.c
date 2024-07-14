#include "handle_insert.h"
#include "../globals/terminal_setting.h"
#include <string.h>
int popMiddle(char middle[], int index) {

  int temp_index = index;
  char temp_char = middle[index];
  while (temp_char != '\0') {
    middle[temp_index] = middle[temp_index + 1];
    temp_index++;
    temp_char = middle[temp_index];
  }
  return 0;
}

int appendMiddle(char middle[], int index, char new_char) {

  char temp_char = middle[index];
  char old_char = new_char;
  int temp_index = index;
  while (temp_char != '\0') {
    middle[temp_index] = old_char;
    old_char = temp_char;
    temp_index++;
    temp_char = middle[temp_index];
  }
  middle[temp_index] = old_char;
  middle[temp_index + 1] = temp_char;
  return 0;
}

int newLine(char (*file_content)[1024], int index, int *line_count) {
  for (int i = *line_count; i > index; i--) {
    strcpy_s(file_content[i], 1024, file_content[i - 1]);
  }
  file_content[index][0] = '\n';
  file_content[index][1] = '\0';
  *line_count += 1;
  return 0;
}

int delLine(char (*file_content)[1024], int index, int *line_count) {
  for (int i = index; i < *line_count; i++) {
    strcpy_s(file_content[i], 1024, file_content[i + 1]);
  }
  file_content[*line_count - 1][0] = '\0';
  *line_count -= 1;
  return 0;
}

int handle_insert(char key, BoxCords *mouse_cords, BoxCords *real_mouse_cords,
                  WriteMode *write_mode, int *running,
                  char (*file_content)[1024], int *line_count) {
  int key_code = key;
  if (key_code < 48) {
    switch (key_code) {
    case 8:
      if (mouse_cords->x != min_x) {
        popMiddle(file_content[mouse_cords->y - min_y],
                  mouse_cords->x - min_x - 1);
        mouse_cords->x--;
        real_mouse_cords->x--;
      } else {
        delLine(file_content, mouse_cords->y - min_y, line_count);
        mouse_cords->y--;
        real_mouse_cords->y--;
      }
      break;
    case 13:
      newLine(file_content, mouse_cords->y - min_y, line_count);
      mouse_cords->y++;
      real_mouse_cords->y++;
      break;
    case 32:
      appendMiddle(file_content[mouse_cords->y - min_y], mouse_cords->x - min_x,
                   ' ');
      mouse_cords->x++;
      real_mouse_cords->x++;
      break;
    case 27:
      *write_mode = NORMAL;
      break;
    }
  } else {
    switch (key) {
    default:
      appendMiddle(file_content[mouse_cords->y - min_y], mouse_cords->x - min_x,
                   key);
      mouse_cords->x++;
      real_mouse_cords->x++;
      break;
    }
  }
  return 1;
}
