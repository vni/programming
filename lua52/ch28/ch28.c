#include <string.h>
#include <lua.h>
#include <lauxlib.h>

static int counter(lua_State *L) {
	int val = lua_tointeger(L, lua_upvalueindex(1));
	lua_pushinteger(L, ++val);
	lua_pushvalue(L, -1);
	lua_replace(L, lua_upvalueindex(1));
	return 1;
}

static int l_newCounter(lua_State *L) {
	lua_pushinteger(L, 0);
	lua_pushcclosure(L, &counter, 1);
	return 1;
}

static int l_tconcat(lua_State *L) {
	luaL_Buffer b;
	int i, n;
	luaL_checktype(L, 1, LUA_TTABLE);
	n = luaL_len(L, 1);
	luaL_buffinit(L, &b);
	for (i = 1; i <= n; i++) {
		lua_rawgeti(L, 1, i);
		luaL_addvalue(&b);
	}
	luaL_pushresult(&b);
	return 1;
}

static int l_upper(lua_State *L) {
	size_t l, i;
	luaL_Buffer b;
	const char *s = luaL_checklstring(L, 1, &l);
	char *p = luaL_buffinitsize(L, &b, l);
	for (i = 0; i < l; i++)
		p[i] = toupper((unsigned char)(s[i]));
	luaL_pushresultsize(&b, l);

	return 1;
}

static int l_map(lua_State *L) {
	int i, n;
	luaL_checktype(L, 1, LUA_TTABLE);
	luaL_checktype(L, 2, LUA_TFUNCTION);

	n = luaL_len(L, 1);
	for (i = 1; i <= n; i++) {
		lua_pushvalue(L, 2);
		lua_rawgeti(L, 1, i);
		lua_call(L, 1, 1);
		lua_rawseti(L, 1, i);
	}

	return 0;
}

static int l_split(lua_State *L) {
	const char *s = luaL_checkstring(L, 1);
	const char *sep = luaL_checkstring(L, 2);
	const char *e;
	int i = 1;

	lua_newtable(L);

	while ((e = strchr(s, *sep)) != NULL) {
		lua_pushlstring(L, s, e-s);
		lua_rawseti(L, -2, i++);
		s = e+1;
	}
	lua_pushstring(L, s);
	lua_rawseti(L, -2, i);

	return 1;
}

static struct luaL_Reg ch28_functions[] = {
	{ "newCounter", l_newCounter },
	{ "concat", l_tconcat },
	{ "upper", l_upper },
	{ "map", l_map },
	{ "split", l_split },
	{ NULL, NULL }
};

int luaopen_ch28(lua_State *L) {
	luaL_newlib(L, ch28_functions);
	return 1;
}
