#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>

static int l_table_pack(lua_State *L) {
	int i;
	int n = lua_gettop(L);

	lua_newtable(L);
	lua_pushstring(L, "n");
	lua_pushinteger(L, n);
	lua_settable(L, -3);

	for (i = 1; i <= n; i++) {
		lua_pushinteger(L, i);
		lua_pushvalue(L, i);
		lua_settable(L, -3);
	}

	return 1;
}

int main(void) {
	char buf[256];
	int error;

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	lua_pushcfunction(L, l_table_pack);
	lua_setglobal(L, "mypack");

	printf("\033[34;1mtable.pack>\033[0m ");
	while (fgets(buf, sizeof(buf), stdin) != NULL) {
		error = luaL_loadstring(L, buf) || lua_pcall(L, 0, 0, 0);
		if (error) {
			fprintf(stderr, "%s\n", lua_tostring(L, -1));
			lua_pop(L, 1);
		}
		printf("\033[34;1mtable.pack>\033[0m ");
	}

	lua_close(L);
	return 0;
}
