#include <math.h>
#include <stdio.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int l_sin(lua_State *L) {
	double d = luaL_checknumber(L, 1);
	lua_pushnumber(L, sin(d));
	return 1;
}

static int l_cos(lua_State *L) {
	double d = luaL_checknumber(L, 1);
	lua_pushnumber(L, cos(d));
	return 1;
}

int main(void) {
	char buf[256];
	int error;
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	lua_pushcfunction(L, l_sin);
	lua_setglobal(L, "mysine");

	lua_pushcfunction(L, l_cos);
	lua_setglobal(L, "mycosine");

	printf("\033[34;1m>\033[0m ");
	while (fgets(buf, sizeof(buf), stdin)) {
		error = luaL_loadstring(L, buf) || lua_pcall(L, 0, 0, 0);
		if (error) {
			fprintf(stderr, "%s\n", lua_tostring(L, -1));
			lua_pop(L, 1);
		}
		printf("\033[34;1m>\033[0m ");
	}

	lua_close(L);
	return 0;
}
