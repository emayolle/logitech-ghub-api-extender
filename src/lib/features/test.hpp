#include <hooks/LuaVMInitializer.h> 

/**
 * @brief THIS IS A TEST FUNCTION TO TEST THE LUA VM
 */
int test(lua_State* L) {
    LuaVM vm = LuaVM(L);

    return 0;
}
