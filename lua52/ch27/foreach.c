#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>

static void dumpStack(lua_State *L) {
	int i, n;

	printf("===> stack dump\n");
	n = lua_gettop(L);
	for (i = 1; i <= n; i++)
		switch (lua_type(L, i)) {
			case LUA_TNIL:
				printf("\tNIL\n");
				break;
			case LUA_TBOOLEAN:
				printf("\t%s\n", lua_toboolean(L, i) ? "true" : "false");
				break;
			case LUA_TNUMBER:
				printf("\t%.4g\n",  lua_tonumber(L, i));
				break;
			case LUA_TSTRING:
				printf("\t\"%s\"\n", lua_tostring(L, i));
				break;
			case LUA_TTABLE:
				printf("\tTABLE\n");
				break;
			case LUA_TFUNCTION:
				printf("\tFUNCTION\n");
				break;
			default:
				printf("\tUNKNOWN TYPE: %s\n", lua_typename(L, i));
				break;
		}
	printf(">=== end of stack dump\n");
}

static int l_foreach(lua_State *L) {
	luaL_checktype(L, 1, LUA_TTABLE);
	luaL_checktype(L, 2, LUA_TFUNCTION);

	lua_pushvalue(L, 2);
	lua_pushnil(L);
	while (lua_next(L, 1) != 0) {
		/*dumpStack(L);*/
		lua_pushvalue(L, -2);
		lua_insert(L, -4);
		/*dumpStack(L);*/
		lua_call(L, 2, 0);
		/*dumpStack(L);*/
		/*printf("===========================================\n");*/
		lua_pushvalue(L, 2);
		lua_insert(L, -2);
	}
	lua_pop(L, 1); /* pop up the last key and function */
	/*printf("final stack:\n");*/
	/*dumpStack(L);*/

	return 0;
}

int main(void) {
	char buf[256];
	int error;

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	lua_pushcfunction(L, l_foreach);
	lua_setglobal(L, "foreach");

	printf("\033[34;1mforeach>\033[0m ");
	while (fgets(buf, sizeof(buf), stdin) != NULL) {
		error = luaL_loadstring(L, buf) || lua_pcall(L, 0, 0, 0);
		if (error) {
			fprintf(stderr, "%s\n", lua_tostring(L, -1));
			lua_pop(L, 1);
		}
		printf("\033[34;1mforeach>\033[0m ");
	}

	lua_close(L);
	return 0;
}
