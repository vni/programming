#include <lua.h>
#include <lauxlib.h>

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void error(lua_State *L, const char *fmt, ...) {
	va_list argp;
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	lua_close(L);
	exit(EXIT_FAILURE);
}

double f(lua_State *L, double x, double y) {
	int isnum;
	double z;

	lua_getglobal(L, "f");
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);

	if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
		error(L, "error running function 'f': %s",
				lua_tostring(L, -1));
		lua_pop(L, 1);
	}

	z = lua_tonumberx(L, -1, &isnum);
	if (!isnum) {
		error(L, "function 'f' must return a number");
		lua_pop(L, 1);
	}
	lua_pop(L, 1);
	return z;
}

int main(void) {
	double x, y, z;
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	if (luaL_loadfile(L, "f.lua") || lua_pcall(L, 0, 0, 0)) {
		error(L, "cannot load and call f.lua: %s\n",
				lua_tostring(L, -1));
		lua_pop(L, 1);
	}

	for (x = 0.0; x < 10; x += 2.5)
		for (y = 0.0; y < 5; y += 0.5) {
			z = f(L, x, y);
			printf("%g = f(%f, %g)\n", z, x, y);
		}

	lua_close(L);
	return 0;
}
