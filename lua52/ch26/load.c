#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <lua.h>
#include <lauxlib.h>

#define MAX_COLOR 255

struct ColorTable {
	char *name;
	unsigned char red, green, blue;
} colortable[] = {
	{ "BLACK",          0,         0,         0 },
	{ "RED",    MAX_COLOR,         0,         0 },
	{ "GREEN",          0, MAX_COLOR,         0 },
	{ "BLUE",           0,         0, MAX_COLOR },
	{ "YELLOW", MAX_COLOR, MAX_COLOR,         0 },
	{ "PURPLE", MAX_COLOR,         0, MAX_COLOR },
	{ "CYAN",           0, MAX_COLOR, MAX_COLOR },
	{ "WHITE",  MAX_COLOR, MAX_COLOR, MAX_COLOR },
	{ NULL,             0,         0,         0 },
};

void error(lua_State *L, const char *fmt, ...) {
	va_list argp;
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	lua_close(L);
	exit(EXIT_FAILURE);
}

int getcolorfield(lua_State *L, const char *key) {
	int result;
	/* lua_pushstring(L, key);
	lua_gettable(L, -2); */
	lua_getfield(L, -1, key);
	if (!lua_isnumber(L, -1))
		error(L, "invalid component in background color\n");
	result = (int)(lua_tonumber(L, -1) * MAX_COLOR);
	lua_pop(L, 1);
	return result;
}

void setcolorfield(lua_State *L, const char *key, int value) {
	/*lua_pushstring(L, key);*/
	lua_pushnumber(L, (double)value / MAX_COLOR);
	/*lua_settable(L, -3);*/
	lua_setfield(L, -2, key);
}

void setcolor(lua_State *L, struct ColorTable *ct) {
	lua_newtable(L);
	setcolorfield(L, "r", ct->red);
	setcolorfield(L, "g", ct->green);
	setcolorfield(L, "b", ct->blue);
	lua_setglobal(L, ct->name);
}

void load(lua_State *L, const char *fname, int *w, int *h,
		unsigned char *red, unsigned char *green, unsigned char *blue) {
	if (luaL_loadfile(L, fname) || lua_pcall(L, 0, 0, 0))
		error(L, "cannot run config file: %s\n", lua_tostring(L, -1));
	lua_getglobal(L, "width");
	lua_getglobal(L, "height");
	if (!lua_isnumber(L, -2))
		error(L, "'width' should be a number\n");
	if (!lua_isnumber(L, -1))
		error(L, "'height' should be a number\n");
	*w = lua_tointeger(L, -2);
	*h = lua_tointeger(L, -1);

	lua_getglobal(L, "background");
	if (lua_isstring(L, -1)) {
		const char *colorname = lua_tostring(L, -1);
		int i;
		for (i = 0; colortable[i].name != NULL; i++)
			if (strcasecmp(colorname, colortable[i].name) == 0)
				break;
		if (colortable[i].name == NULL) {
			error(L, "invalid color name (%s)\n", colorname);
		} else {
			*red = colortable[i].red;
			*green = colortable[i].green;
			*blue = colortable[i].blue;
		}
	} else if (lua_istable(L, -1)) {
		*red = getcolorfield(L, "r");
		*green = getcolorfield(L, "g");
		*blue = getcolorfield(L, "b");
	} else
		error(L, "invalid value for 'background'\n");
}

int main(int argc, char *argv[]) {
	int i;
	int width, height;
	unsigned char red, green, blue;
	const char *fname = "conf.lua"; /* default */
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	if (argc > 1)
		fname = argv[1];

	for (i = 0; colortable[i].name != NULL; ++i)
		setcolor(L, &colortable[i]);

	load(L, fname, &width, &height, &red, &green, &blue);
	printf("width: %d, height: %d\n", width, height);
	printf("red: %d, green: %d, blue: %d\n", red, green, blue);

	return 0;
}
