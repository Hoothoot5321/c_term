#include "settings.h"
#include "colors.h"
#include "terminal_setting.h"

#include "../include/lauxlib.h"
#include "../include/lua.h"
#include "../include/lualib.h"
#include "../structs/dimensions.h"
#include "../terminal_handlers/get_term_size.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char bg_col[20];

char text_col[20];

char line_num_col[20];

char insert_header_bg_col[20];

char normal_header_bg_col[20];

char insert_header_text_col[20];

char normal_header_text_col[20];

int min_x;

int min_y;

int relative_lines;

BoxDimension terminal_dimensions;
const char *getLuaVariableS(lua_State *L, char *variable_name) {

  lua_getglobal(L, variable_name);
  if (lua_isstring(L, -1)) {
    const char *msg = lua_tostring(L, -1);
    lua_pop(L, 1);
    return msg;
  }
  return NULL;
}

int getLuaVariableB(lua_State *L, char *variable_name) {

  lua_getglobal(L, variable_name);
  if (lua_isboolean(L, -1)) {
    int msg = lua_toboolean(L, -1);
    lua_pop(L, 1);
    return msg;
  }
  return 0;
}

int getLuaVariableI(lua_State *L, char *variable_name) {

  lua_getglobal(L, variable_name);
  if (lua_tointeger(L, -1)) {
    int msg = lua_tointeger(L, -1);
    return msg;
  }
  return 0;
}

int setupSettings() {
  int terminal_err = getTermSize(&terminal_dimensions);
  if (terminal_err == -1) {
    return terminal_err;
  }
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  if (luaL_dofile(L, "init.lua") == LUA_OK) {
    lua_pop(L, lua_gettop(L));
  }

  int bg_trans = getLuaVariableB(L, "Bg_transparent");

  if (bg_trans) {
    strcpy_s(bg_col, 20, "\e[49m\0");
  } else {
    const char *temp_bg_col = getLuaVariableS(L, "Bg_col");
    sprintf_s(bg_col, 20, "\e[48;5;%sm", temp_bg_col);
    strcat_s(bg_col, 20, "\0");
  }

  const char *temp_text_col = getLuaVariableS(L, "Text_col");
  sprintf_s(text_col, 20, "\e[38;5;%sm", temp_text_col);
  strcat_s(text_col, 20, "\0");

  const char *temp_line_num_col = getLuaVariableS(L, "Line_num_col");
  sprintf_s(line_num_col, 20, "\e[38;5;%sm", temp_line_num_col);
  strcat_s(line_num_col, 20, "\0");

  const char *temp_insert_header_bg_col = getLuaVariableS(L, "I_h_bg_col");
  sprintf_s(insert_header_bg_col, 20, "\e[48;5;%sm", temp_insert_header_bg_col);
  strcat_s(insert_header_bg_col, 20, "\0");

  const char *temp_normal_header_bg_col = getLuaVariableS(L, "N_h_bg_col");
  sprintf_s(normal_header_bg_col, 20, "\e[48;5;%sm", temp_normal_header_bg_col);
  strcat_s(normal_header_bg_col, 20, "\0");

  const char *temp_insert_header_text_col = getLuaVariableS(L, "I_h_txt_col");
  sprintf_s(insert_header_text_col, 20, "\e[38;5;%sm",
            temp_insert_header_text_col);
  strcat_s(insert_header_text_col, 20, "\0");

  const char *temp_normal_header_text_col = getLuaVariableS(L, "N_h_txt_col");
  sprintf_s(normal_header_text_col, 20, "\e[38;5;%sm",
            temp_normal_header_text_col);
  strcat_s(normal_header_text_col, 20, "\0");

  min_x = getLuaVariableI(L, "X_offset");
  min_y = getLuaVariableI(L, "Y_offset");

  relative_lines = getLuaVariableB(L, "Relative_lines");

  lua_close(L);
  // bg_col = "\e[48;5;17m";
  //  Transparent background
  //  bg_col = "\e[49m";

  // text_col = "\e[38;5;190m";

  // line_num_col = "\e[38;5;3m";
  return 0;
}
