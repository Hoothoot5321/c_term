
#ifndef HANDLE_INSERT_H_
#define HANDLE_INSERT_H_

#include "../structs/box_cords.h"

#include "../enums/states.h"

int handle_insert(char key, BoxCords *mouse_cords, BoxCords *real_mouse_cords,
                  WriteMode *write_mode, int *running,
                  char (*file_content)[1024], int *line_count);

#endif
