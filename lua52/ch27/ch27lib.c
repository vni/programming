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

static int l_reverse(lua_State *L) {
	double sum = 0.0;
	int n = lua_gettop(L);
	int i;

	for (i = 1; i < n; i++) /* do n-1 times */
		lua_insert(L, i);

	return n;
}

static int l_foreach(lua_State *L) {
	luaL_checktype(L, 1, LUA_TTABLE);
	luaL_checktype(L, 2, LUA_TFUNCTION);

	lua_pushvalue(L, 2);
	lua_pushnil(L);
	while (lua_next(L, 1) != 0) {
		lua_pushvalue(L, -2);
		lua_insert(L, -4);
		lua_call(L, 2, 0);
		lua_pushvalue(L, 2);
		lua_insert(L, -2);
	}
	lua_pop(L, 1); /* pop up the last key and function */

	return 0;
}

static struct luaL_Reg ch27_functions[] = {
	{ "summation", l_summation },
	{ "mypack", l_table_pack },
	{ "reverse", l_reverse },
	{ "foreach", l_foreach },
	{ NULL, NULL },
};

int luaopen_ch27lib(lua_State *L) {
	luaL_newlib(L, ch27_functions );
	return 1;
}
