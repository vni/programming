#include <lua.h>
#include <lauxlib.h>

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

static struct luaL_Reg ch28_functions[] = {
	{ "concat", l_tconcat },
	{ "upper", l_upper },
	{ "map", l_map },
	{ NULL, NULL }
};

int luaopen_ch28(lua_State *L) {
	luaL_newlib(L, ch28_functions);
	return 1;
}
