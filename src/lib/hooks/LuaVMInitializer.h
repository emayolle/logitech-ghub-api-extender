#pragma once
#ifndef _LUA_VM_INITIALIZER_H
#define _LUA_VM_INITIALIZER_H
#include <iostream>
#include <windows.h>
#include <LuaVM.hpp>

extern "C" {
    #include <lua/lua.h>
    #include <lua/lauxlib.h>
    #include <lua/lualib.h>
}

typedef __int64(*tLuaVMInitializer)(__int64 luaVirtualMachine, __int64 a2, __int64 *a3);
inline tLuaVMInitializer LuaVMInitializer = nullptr;

__int64 hkLuaVMInitializer(__int64 luaVirtualMachine, __int64 a2, __int64 *a3);
#endif // _LUA_VM_INITIALIZER_H