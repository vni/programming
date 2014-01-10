#include <lua.h>
#include <lauxlib.h>

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

void error(lua_State *L, const char *fmt, ...) {
	va_list argp;
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	lua_close(L);
	exit(EXIT_FAILURE);
}

void call_va(lua_State *L, const char *func, const char *sig, ...) {
	va_list vl;
	int narg, nres;

	va_start(vl, sig);
	lua_getglobal(L, func);

	for (narg = 0; *sig; narg++) {
		luaL_checkstack(L, 1, "too many arguments");

		switch (*sig++) {
			case 'd':
				lua_pushnumber(L, va_arg(vl, double));
				break;
			case 'i':
				lua_pushinteger(L, va_arg(vl, int));
				break;
			case 'b':
				lua_pushboolean(L, va_arg(vl, int));
				break;
			case 's':
				lua_pushstring(L, va_arg(vl, char *));
				break;
			case '>':
				goto endargs;
			default:
				error(L, "invalid option (%c)", *(sig - 1));
		}
	}
endargs:

	nres = strlen(sig);

	if (lua_pcall(L, narg, nres, 0) != 0)
		error(L, "error calling '%s': %s\n", func, lua_tostring(L, -1));

	nres = -nres;
	while (*sig) {
		switch (*sig++) {
			case 'd': {
				int isnum;
				double n = lua_tonumberx(L, nres, &isnum);
				if (!isnum)
					error(L, "wrong result type\n");
				*va_arg(vl, double *) = n;
				break;
			}
			case 'i': {
				int isnum;
				int n = lua_tointegerx(L, nres, &isnum);
				if (!isnum)
					error(L, "wrong result type\n");
				*va_arg(vl, int *) = n;
				break;
			}
			case 'b': {
				int n = lua_toboolean(L, nres);
				*va_arg(vl, int *) = n;
				break;
			}
			case 's': {
				const char *s = lua_tostring(L, nres);
				if (s == NULL)
					error(L, "wrong result type\n");
				*va_arg(vl, const char **) = s;
				break;
			}
			default:
				error(L, "invalid option (%c)", *(sig - 1));
		}
		nres++;
	}

	va_end(vl);
}

int main(void) {
	int x, y, z = 1, sum, bool1, bool2;
	const char *s;
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	if (luaL_loadfile(L, "g.lua") || lua_pcall(L, 0, 0, 0)) {
		error(L, "cannot load and call f.lua: %s\n",
				lua_tostring(L, -1));
		lua_pop(L, 1);
	}

	for (x = 0; x < 10; x++)
		for (y = x; y < 10; y++) {
			call_va(L, "g", "iii>bbis", x, y, z, &bool1, &bool2, &sum, &s);
			printf("%d, %d, %d, %s = g(%d, %d, %d)\n", bool1, bool2, sum, s, x, y, z);
		}

	lua_close(L);
	return 0;
}
