#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <string.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#define DEBUG  NULL
struct THEME { char* name; };
struct FONT {char* name;  char* size;};

struct THEME *change_theme(char* f){
	struct THEME *t;
	t = malloc(sizeof(struct THEME));
	
	lua_State *L = luaL_newstate();	
	luaL_openlibs(L);
   	luaL_dofile(L, f);
	lua_getglobal(L, "theme");
	if (lua_istable(L, -1)) {
		lua_getfield(L, -1, "name");
	    char *theme = (char* ) lua_tostring(L, -1);
		t->name = theme;
	}
	return t;
}

struct FONT *change_font(char* f){
	struct FONT *fo;
	fo = malloc(sizeof(struct FONT));
	lua_State *L = luaL_newstate();	
	luaL_openlibs(L);
	luaL_dofile(L, f);
	lua_getglobal(L, "font");
	if (lua_istable(L, -1)) {
		lua_getfield(L, -1, "name");
		char *f_name = (char* )lua_tostring(L, -1);
		fo->name = f_name;
		lua_getfield(L, -2, "size");
		char *f_size = (char* )lua_tostring(L, -1);
		fo->size = f_size;
	}
	return fo;
}

int main(int argc, char *argv[])
{

	char* file = "test.lua";
	if (access(file, F_OK) == -1) {
		perror("Error");
		exit(0);
	}
	
    struct FONT*  f  = change_font(file);  
	struct THEME* t = change_theme(file); 

#ifdef DEBUG
	printf("%s\n", t->name);
	printf("%s\n", f->name);
	printf("%s\n", f->size);
#endif

	free(t);
	free(f);
	return 0;
}
