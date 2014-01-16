#include <lua.h>
#include <lauxlib.h>

static int t_tuple(lua_State *L) {
	int op = luaL_optint(L, 1, 0);
	if (op == 0) {
		int i;
		for (i = 1; !lua_isnone(L, lua_upvalueindex(i)); i++)
			lua_pushvalue(L, lua_upvalueindex(i));
		return i - 1;
	} else {
		luaL_argcheck(L, 0 < op, 1, "index out of range");
		if (lua_isnone(L, lua_upvalueindex(op)))
			return 0;
		lua_pushvalue(L, lua_upvalueindex(op));
		return 1;
	}
}

static int t_new(lua_State *L) {
	lua_pushcclosure(L, &t_tuple, lua_gettop(L));
	return 1;
}

static struct luaL_Reg tuplelib[] = {
	{ "new", t_new },
	{ NULL, NULL }
};

int luaopen_tuple(lua_State *L) {
	luaL_newlib(L, tuplelib);
	return 1;
}
