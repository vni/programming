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

static int l_transliterate(lua_State *L) {
	size_t len;
	int i;
	const char *str = luaL_checklstring(L, 1, &len);
	luaL_checktype(L, 2, LUA_TTABLE);
	char key[2] = { 0, 0 };
	luaL_Buffer buf;
	char *p = luaL_buffinitsize(L, &buf, len);
	const char * const buf_start = p;

	for (i = 0; i < len; i++) {
		key[0] = str[i];
		lua_getfield(L, 2, key);
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
	{ "filter", l_filter },
	{ "split", l_split },
	{ "transliterate", l_transliterate },
	{ NULL, NULL },
};

int luaopen_exercies(lua_State *L) {
	luaL_newlib(L, R);
	return 1;
}
