#include <string.h>
#include <lua.h>
#include <lauxlib.h>

static int l_settrans(lua_State *L) {
	luaL_checktype(L, -1, LUA_TTABLE);
	lua_setfield(L, LUA_REGISTRYINDEX, "transliterate.transtable");
	return 0;
}

static int l_gettrans(lua_State *L) {
	lua_getfield(L, LUA_REGISTRYINDEX, "transliterate.transtable");
	return 1;
}

static int l_transliterate(lua_State *L) {
	size_t len;
	int i;
	const char *str = luaL_checklstring(L, 1, &len);
	char key[2] = { 0, 0 };
	luaL_Buffer buf;
	char *p = luaL_buffinitsize(L, &buf, len);
	const char * const buf_start = p;
	lua_getfield(L, LUA_REGISTRYINDEX, "transliterate.transtable");

	for (i = 0; i < len; i++) {
		key[0] = str[i];
		lua_getfield(L, -1, key);
		if (!lua_isnil(L, -1)) {
			if (lua_isboolean(L, -1)) {
				int b = lua_toboolean(L, -1);
				if (b == 0) /* false */ {
				} else {
					luaL_error(L, "Error: expected false as boolean value in transliterate table");
				}
			} else if (lua_isstring(L, -1)) {
				const char *v = lua_tostring(L, -1);
				*p++ = *v;
			} else {
				luaL_error(L, "Error: expected boolean or string values in transliterate table");
			}
		} else {
			*p++ = str[i];
		}
		lua_pop(L, 1);
	}

	luaL_pushresultsize(&buf, p - buf_start);
	return 1;
}

static struct luaL_Reg R[] = {
	{ "settrans", l_settrans },
	{ "gettrans", l_gettrans },
	{ "transliterate", l_transliterate },
	{ NULL, NULL },
};

int luaopen_registry_transliterate(lua_State *L) {
	luaL_newlib(L, R);
	return 1;
}
