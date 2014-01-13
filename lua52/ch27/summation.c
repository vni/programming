#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>

static int l_summation(lua_State *L) {
	double sum = 0.0;
	int n = lua_gettop(L);
	int i;

	for (i = 1; i <= n; i++)
		sum += luaL_checknumber(L, i);

	lua_pushnumber(L, sum);

	return 1;
}

int main(void) {
	char buf[256];
	int error;

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	lua_pushcfunction(L, l_summation);
	lua_setglobal(L, "summation");

	printf("\033[34;1msummation>\033[0m ");
	while (fgets(buf, sizeof(buf), stdin) != NULL) {
		error = luaL_loadstring(L, buf) || lua_pcall(L, 0, 0, 0);
		if (error) {
			fprintf(stderr, "%s\n", lua_tostring(L, -1));
			lua_pop(L, 1);
		}
		printf("\033[34;1msummation>\033[0m ");
	}

	lua_close(L);
	return 0;
}
