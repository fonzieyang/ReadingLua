#include "lua.hpp"
#include "stdio.h"
#include "string"

int lua_print(lua_State * luastate)
{
	int nargs = lua_gettop(luastate);

	std::string t;
	for (int i=1; i <= nargs; i++)
	{
		if (lua_istable(luastate, i))
			t += "table";
		else if (lua_isnone(luastate, i))
			t += "none";
		else if (lua_isnil(luastate, i))
			t += "nil";
		else if (lua_isboolean(luastate, i))
		{
			if (lua_toboolean(luastate, i) != 0)
				t += "true";
			else
				t += "false";
		}
		else if (lua_isfunction(luastate, i))
			t += "function";
		else if (lua_islightuserdata(luastate, i))
			t += "lightuserdata";
		else if (lua_isthread(luastate, i))
			t += "thread";
		else
		{
			const char * str = lua_tostring(luastate, i);
			if (str)
				t += lua_tostring(luastate, i);
			else
				t += lua_typename(luastate, lua_type(luastate, i));
		}
		if (i!=nargs)
			t += "\t";
	}
	printf("%s", t.c_str());

	return 0;
}


#if 0


int main(){
	lua_State* state = luaL_newstate();
	luaL_openlibs(state);
	const luaL_Reg global_functions [] = {
		{"print", lua_print},
		{NULL, NULL}
	};
	luaL_register(state, "_G", global_functions);
	//luaopen_base(state);
	luaL_dofile(state, "main.lua");
	printf("hello lua");
	return 0;
}
#endif