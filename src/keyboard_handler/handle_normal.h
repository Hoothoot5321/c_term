#ifndef HANDLE_NORMAL_H_
#define HANDLE_NORMAL_H_

#include "../structs/box_cords.h"

#include "../enums/states.h"

int handle_normal(char key, BoxCords *mouse_cords, BoxCords *real_mouse_cords,
                  WriteMode *write_mode, int *running,
                  char (*file_content)[1024], int *line_count);

#endif
