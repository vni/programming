#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>

static int l_reverse(lua_State *L) {
	double sum = 0.0;
	int n = lua_gettop(L);
	int i;

	for (i = 1; i < n; i++) /* do n-1 times */
		lua_insert(L, i);

	return n;
}

int main(void) {
	char buf[256];
	int error;

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	lua_pushcfunction(L, l_reverse);
	lua_setglobal(L, "reverse");

	printf("\033[34;1mreverse>\033[0m ");
	while (fgets(buf, sizeof(buf), stdin) != NULL) {
		error = luaL_loadstring(L, buf) || lua_pcall(L, 0, 0, 0);
		if (error) {
			fprintf(stderr, "%s\n", lua_tostring(L, -1));
			lua_pop(L, 1);
		}
		printf("\033[34;1mreverse>\033[0m ");
	}

	lua_close(L);
	return 0;
}
