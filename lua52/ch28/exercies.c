#include <lua.h>
#include <lauxlib.h>

static int l_filter(lua_State *L) {
	int i, j, n, res;
	luaL_checktype(L, 1, LUA_TTABLE);
	luaL_checktype(L, 2, LUA_TFUNCTION);

	n = luaL_len(L, 1);

	lua_newtable(L);
	for (j = i = 1; i <= n; i++) {
		lua_pushvalue(L, 2);
		lua_rawgeti(L, 1, i);
		lua_call(L, 1, 1);

		res = lua_toboolean(L, -1);
		lua_pop(L, 1);
		if (res) {
			lua_rawgeti(L, 1, i);
			lua_rawseti(L, -2, j);
			j++;
		}
	}

	return 1;
}

static struct luaL_Reg R[] = {
	{ "filter", l_filter },
	{ NULL, NULL },
};

int luaopen_exercies(lua_State *L) {
	luaL_newlib(L, R);
	return 1;
}
