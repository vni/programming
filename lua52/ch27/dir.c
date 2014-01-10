#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <dirent.h>
#include <errno.h>

static int l_dir(lua_State *L) {
	DIR *dir;
	struct dirent *entry;
	int i;
	const char *path = luaL_checkstring(L, 1);

	dir = opendir(path);
	if (dir == NULL) {
		lua_pushnil(L);
		lua_pushstring(L, strerror(errno));
		return 2;
	}

	lua_newtable(L);
	i = 1;
	while ((entry = readdir(dir)) != NULL) {
		lua_pushnumber(L, i++);
		lua_pushstring(L, entry->d_name);
		lua_settable(L, -3);
	}

	closedir(dir);
	return 1;
}

int main(void) {
	char buf[256];
	int error;

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	lua_pushcfunction(L, l_dir);
	lua_setglobal(L, "dir");

	printf("\033[34;1m>\033[0m ");
	while (fgets(buf, sizeof(buf), stdin) != NULL) {
		error = luaL_loadstring(L, buf) || lua_pcall(L, 0, 0, 0);
		if (error) {
			fprintf(stderr, "%s\n", lua_tostring(L, -1));
			lua_pop(L, 1);
		}
		printf("\033[34;1m>\033[0m ");
	}

	lua_close(L);
	return 0;
}
