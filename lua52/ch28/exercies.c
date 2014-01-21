#include <string.h>
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

static int l_split(lua_State *L) {
	size_t len = 0;
	const char *s = luaL_checklstring(L, 1, &len);
	const char * const start = s;
	const char *sep = luaL_checkstring(L, 2);
	const char *e;
	int i = 1;

	lua_newtable(L);

	while ((e = memchr(s, *sep, len-(s-start))) != NULL) {
		lua_pushlstring(L, s, e-s);
		lua_rawseti(L, -2, i++);
		s = e+1;
	}
	lua_pushstring(L, s);
	lua_rawseti(L, -2, i);

	return 1;
}

static struct luaL_Reg R[] = {
	{ "filter", l_filter },
	{ "split", l_split },
	{ NULL, NULL },
};

int luaopen_exercies(lua_State *L) {
	luaL_newlib(L, R);
	return 1;
}
