#include "LuaVMInitializer.h"

#include <features/luaprint.hpp>
#include <features/MessageBox.hpp>
#include <features/test.hpp>

#define DeclLuaFunction(vm, func, name) \
    vm.PushCFunction(func); \
    vm.SetGlobal(name);

/**
 * @brief The hook for the LuaVMInitializer function.
 * param luaVirtualMachine The Lua virtual machine.
 * param a2 Unknown.
 * param a3 Unknown.
 * return The result of the original LuaVMInitializer function.
 */
__int64 hkLuaVMInitializer(__int64 luaVirtualMachine, __int64 a2, __int64 *a3)
{
    static bool first = true;
    __int64 result = LuaVMInitializer(luaVirtualMachine, a2, a3);

    LuaVM vm = LuaVM(*(lua_State **)(luaVirtualMachine + 48));

    DeclLuaFunction(vm, luaprint, "print");
    DeclLuaFunction(vm, MessageBoxLua, "MessageBox");
    DeclLuaFunction(vm, test, "test"); /* Only if you plan to test the Lua VM */

    return result;
}