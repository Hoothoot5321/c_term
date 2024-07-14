#ifndef READ_FILE_H_
#define READ_FILE_H_

#include <stddef.h>
int readFile(char (*file_content)[1024], const char *file_name,
             size_t line_capacity);

#endif
