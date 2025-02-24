#include <hooks/LuaVMInitializer.h> 

/**
 * @brief Creates a message box with the given title and message.
 * @param title The title of the message box.
 * @param message The message of the message box.
 */
int MessageBoxLua(lua_State* L) {
    LuaVM vm = LuaVM(L);

    const char* title = vm.ToString(1);
    const char* message = vm.ToString(2);
    MessageBoxA(0, message, title, MB_ICONINFORMATION);
    return 0;
}