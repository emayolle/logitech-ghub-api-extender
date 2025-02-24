#include <hooks/LuaVMInitializer.h> 

/**
 * @brief Prints the arguments to the console. (Print in the LGHUB Console and automatically adds a newline)
 * @param ... The arguments to print. (Any type)
 */
int luaprint(lua_State* L) {
    LuaVM vm = LuaVM(L);

    int n = vm.GetTop();  /* number of arguments */
    int i;

    vm.GetGlobal("tostring");

    string str = "";

    for (i = 1; i <= n; i++) {
        const char* s;
        vm.PushValue(-1); /* push tostring */
        vm.PushValue(i); /* value to print */
        vm.Call(1, 1); /* call tostring */
        s = vm.ToString(-1);  /* get result */

        if (s == NULL)
            return vm.Error(LUA_QL("tostring") " must return a string to " LUA_QL("print")); /* result is not a string */

        if (i > 1) str += "    "; 
        str += s;
        vm.Pop(1);  /* pop result */
    }

    vm.Pop(1);  /* pop tostring */

    vm.GetGlobal("OutputLogMessage"); /* Get the OutputLogMessage function */
    vm.PushString((str + "\n").c_str()); /* Push the string to print */
    vm.PCall(1, 0, 0); 

    return 0;
}
