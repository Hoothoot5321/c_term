cmake_minimum_required(VERSION 3.10)
project(CTerm)


add_executable(CTerm
  src/main.c

  src/file_handlers/read_file.c

  src/terminal_handlers/get_term_size.c
  src/terminal_handlers/out_terminal.c

  src/globals/settings.c

  src/keyboard_handler/handle_normal.c
  src/keyboard_handler/handle_insert.c

)


TARGET_LINK_LIBRARIES(CTerm C:/Users/MartinNammat/Documents/Programming-2/Projects/CTerminalText/lua54.lib)


