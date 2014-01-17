/*
 * lua library to check if shared upvalues (see ch28 'Shared Upvalues')
 * really share upvalues or just all upvalues have the same initial value
 */

#include <lua.h>
#include <lauxlib.h>

static int l_a(lua_State *L) {
	int common;

	lua_pushvalue(L, lua_upvalueindex(1));
	lua_getfield(L, -1, "common");
	common = lua_tonumber(L, -1);
	lua_pop(L, 1);
	common += 1;
	lua_pushinteger(L, common);
	lua_setfield(L, -2, "common"); /* update value in shared-upvalue-table */
	lua_pushinteger(L, common);

	return 1;
}

static int l_b(lua_State *L) {
	int common;

	lua_pushvalue(L, lua_upvalueindex(1));
	lua_getfield(L, -1, "common");
	common = lua_tonumber(L, -1);
	lua_pop(L, 1);
	common += 2;
	lua_pushinteger(L, common);
	lua_setfield(L, -2, "common"); /* update value in shared-upvalue-table */
	lua_pushinteger(L, common);

	return 1;
}

static int l_c(lua_State *L) {
	int common;

	lua_pushvalue(L, lua_upvalueindex(1));
	lua_getfield(L, -1, "common");
	common = lua_tonumber(L, -1);
	lua_pop(L, 1);
	common += 3;
	lua_pushinteger(L, common);
	lua_setfield(L, -2, "common"); /* update value in shared-upvalue-table */
	lua_pushinteger(L, common);

	return 1;
}

static luaL_Reg R[] = {
	{ "a", l_a },
	{ "b", l_b },
	{ "c", l_c },
	{ NULL, NULL }
};

int luaopen_single_shared_upvalue(lua_State *L) {
	luaL_newlibtable(L, R);

	/* all function have reference to this table
	 * of common upvalues */
	lua_newtable(L);
	lua_pushinteger(L, 0);
	lua_setfield(L, -2, "common");

	luaL_setfuncs(L, R, 1);

	return 1;
}
