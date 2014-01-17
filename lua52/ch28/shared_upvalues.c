/*
 * lua library to check if shared upvalues (see ch28 'Shared Upvalues')
 * share upvalues or just all upvalues have the same initial value
 */

#include <lua.h>
#include <lauxlib.h>

static int l_a(lua_State *L) {
	int common, val;

	lua_pushvalue(L, lua_upvalueindex(1));
	lua_getfield(L, -1, "common");
	common = lua_tonumber(L, -1);
	lua_pop(L, 1);
	common += 1;
	lua_pushinteger(L, common);
	lua_setfield(L, -2, "common"); /* update value in shared-upvalue-table */
	lua_pushinteger(L, common);

	val = lua_tointeger(L, lua_upvalueindex(2));
	val += 1;
	lua_pushinteger(L, val);
	lua_pushvalue(L, -1);
	lua_replace(L, lua_upvalueindex(2));

	return 2;
}

static int l_b(lua_State *L) {
	int common, val;

	lua_pushvalue(L, lua_upvalueindex(1));
	lua_getfield(L, -1, "common");
	common = lua_tonumber(L, -1);
	lua_pop(L, 1);
	common += 2;
	lua_pushinteger(L, common);
	lua_setfield(L, -2, "common"); /* update value in shared-upvalue-table */
	lua_pushinteger(L, common);

	val = lua_tointeger(L, lua_upvalueindex(2));
	val += 2;
	lua_pushinteger(L, val);
	lua_pushvalue(L, -1);
	lua_replace(L, lua_upvalueindex(2));

	return 2;
}

static int l_c(lua_State *L) {
	int common, val;

	lua_pushvalue(L, lua_upvalueindex(1));
	lua_getfield(L, -1, "common");
	common = lua_tonumber(L, -1);
	lua_pop(L, 1);
	common += 3;
	lua_pushinteger(L, common);
	lua_setfield(L, -2, "common"); /* update value in shared-upvalue-table */
	lua_pushinteger(L, common);

	val = lua_tointeger(L, lua_upvalueindex(2));
	val += 3;
	lua_pushinteger(L, val);
	lua_pushvalue(L, -1);
	lua_replace(L, lua_upvalueindex(2));

	return 2;
}

static luaL_Reg R[] = {
	{ "a", l_a },
	{ "b", l_b },
	{ "c", l_c },
	{ NULL, NULL }
};

int luaopen_shared_upvalues(lua_State *L) {
	luaL_newlibtable(L, R);

	/* all function have reference to this table
	 * of common upvalues */
	lua_newtable(L);
	lua_pushinteger(L, 0);
	lua_setfield(L, -2, "common");

	/* all functions have individual instance of the upvalue
	 * with the same initial value */
	lua_pushinteger(L, 0);

	luaL_setfuncs(L, R, 2);

	return 1;
}
