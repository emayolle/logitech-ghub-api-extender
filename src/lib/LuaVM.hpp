#include <string.h>
#include <PatternScanner.h>

extern "C" {
    #include <lua/lua.h>
    #include <lua/lauxlib.h>
    #include <lua/lualib.h>
}

using namespace PatternScanner;
using namespace std;

#ifndef LUAVM_H
#define LUAVM_H

#define LUA_QL(x)	"'" x "'"
#define LUA_QS		LUA_QL("%s")


static uintptr_t lghub_agent = (uintptr_t)GetModuleHandleA("lghub_agent.exe");

class LuaVM
{
public:
	lua_State* L;
	LuaVM(lua_State* L)
	{
		this->L = L;
	};
	int GetTop() const { return lua_gettop(L); };
	void SetTop(int i) const { lua_settop(L, i); };
	void Call(int n, int r) const { 
		// If pattern not work you can search string "__pairs" it should be the 2nd function called with 5 arguments (a1, 1, 3, 0, 0)
		static auto pattern = CREATE_PATTERN("48 89 5C 24 ? 57 48 83 EC ? 8D 42", 0, PatternScanner::PatternType::ADDRESS);
    	static auto address = PatternScanner::FindPattern(pattern, "lghub_agent.exe");
		
		reinterpret_cast<__int64 (*)(lua_State* a1, int a2, int a3, __int64 a4, __int64 a5)>(address)(L, (n), (r), 0, NULL);
	};
	int PCall(int n, int r, int f) const { 
		// If pattern not work you can search string "=(debug command)" it should be the function called just after with 6 arguments (a1, 0, 0, 0, 0, 0)
		static auto pattern = CREATE_PATTERN("48 89 74 24 ? 57 48 83 EC ? 33 F6 48 89 6C 24", 0, PatternScanner::PatternType::ADDRESS);
    	static auto address = PatternScanner::FindPattern(pattern, "lghub_agent.exe");
		
		return reinterpret_cast<int (*)(lua_State* a1, int a2, int a3, int a4, __int64 a5, __int64 a6)>(address)(L, (n), (r), (f), 0, NULL);
	};
	int RYield(int n) const { return lua_yield(L, n); };
	void GetField(int i, const char* k) const { lua_getfield(L, i, k); };
	void SetField(int i, const char* k) const { lua_setfield(L, i, k); };
	void GetGlobal(const char* k) const { lua_getglobal(L, k); };
	void SetGlobal(const char* k) const { lua_setglobal(L, k); };
	void CreateTable() const { lua_createtable(L, 0, 0); };
	void SetTable(int i) const { lua_settable(L, i); };
	int GetMetaTable(int i) const { return lua_getmetatable(L, i); };
	int SetMetaTable(int i) const { return lua_setmetatable(L, i); };
	void Pop(int n) const { lua_settop(L, -(n)-1); };
	void Insert(int idx) const { lua_insert(L, idx); };
	void Remove(int idx) const { lua_remove(L, idx); };
	int Error() const { return lua_error(L); };
	int Error(const char* fmt) const { return luaL_error(L, fmt); };
	int ArgCheck(bool cond, int numarg, const char* extramsg) const { return cond || luaL_argerror(L, numarg, extramsg); };
	int Next(int idx) const { return lua_next(L, idx); };
	int Type(int i) const { return lua_type(L, i); };
	void PushValue(int i) const { lua_pushvalue(L, i); };
	void PushLightUserData(void* p) const { lua_pushlightuserdata(L, p); };
	void PushNil() const { lua_pushnil(L); };
	void PushNumber(double n) const { lua_pushnumber(L, n); };
	void PushInteger(int n) const { lua_pushinteger(L, n); };
	void PushString(const char* s) const { lua_pushstring(L, s); };
	void PushLString(const char* s, size_t l) const { lua_pushlstring(L, s, l); };
	void PushCClosure(lua_CFunction fn, int n) const { lua_pushcclosure(L, fn, n); };
    void PushCFunction(lua_CFunction fn) const { this->PushCClosure(fn, 0); };
	//void PushCFunction(lua_CFunction fn) const { return _PushCFunction(this, fn); };
	//void _PushCFunction(const LuaVM::GL* GL, lua_CFunction cF) const {
	//	const auto CC = new DevkitCClosure();
	//	CC->Address = (DWORD)cF;
	//	CC->ExtraSpace = 0;
	//	GL->PushLightUserData(CC);
	//	//GL->PushCClosure(CallcheckHook, 1);
	//};
	void PushBoolean(bool b) const { lua_pushboolean(L, b); };
	//void PushRawObject(uintptr_t o, int type) const
	//{
	//	StkId& Top = *(StkId*)((DWORD)L + L_TOP);
	//	Top->tt = type;
	//	Top->value.p = (void*)o;
	//	Top++; // Not sure if this is correct
	//}
	int GetStack(int level, lua_Debug* ar) const { return lua_getstack(L, level, ar); };
	int GetInfo(const char* what, lua_Debug* ar) const { return lua_getinfo(L, what, ar); };
	const char* CheckString(int n) const { return luaL_checklstring(L, n, NULL); };
	const char* CheckString(int n, size_t* l) const { return luaL_checklstring(L, n, l); };
	void CheckType(int n, int t) const { luaL_checktype(L, n, t); };
	void CheckAny(int n) const { luaL_checkany(L, n); };
	//bool IsCFunction(int idx) const { return lua_iscfunction(L, idx); };
	bool IsNumber(int n) const { return lua_isnumber(L, n); };
	bool IsString(int n) const { return lua_isstring(L, n); };
	bool IsUserData(int n) const { return lua_isuserdata(L, n); };
	bool IsFunction(int n) const { return lua_type(L, n) == LUA_TFUNCTION; };
	bool IsTable(int n) const { return lua_type(L, n) == LUA_TTABLE; };
	bool IsLightUserData(int n) const { return lua_type(L, n) == LUA_TLIGHTUSERDATA; };
	bool IsNil(int n) const { return lua_type(L, n) == LUA_TNIL; };
	bool IsBoolean(int n) const { return lua_type(L, n) == LUA_TBOOLEAN; };
	bool IsThread(int n) const { return lua_type(L, n) == LUA_TTHREAD; };
	bool IsNone(int n) const { return lua_type(L, n) == LUA_TNONE; };
	const char* OptString(int n, const char* d) const { return luaL_optlstring(L, n, d, NULL); };
	void* ToPointer(int i) const { return (void*)lua_topointer(L, i); };
	const char* ToString(int i) const { return lua_tolstring(L, i, NULL); };
	const char* ToLString(int i, size_t* l) const { return lua_tolstring(L, i, l); };
	void* ToUserData(int idx) const { return lua_touserdata(L, idx); };
	lua_Integer ToInteger(int i) const { return lua_tointeger(L, i); };
	double ToNumber(int i) const { return lua_tonumber(L, i); };
	bool ToBoolean(int i) const { return lua_toboolean(L, i); };
	
	int Loadbuffer(const char* name, const char* s) const { return luaL_loadbuffer(L, s, strlen(s), name); };
	int Loadstring(const char* s) const { return luaL_loadstring(L, s); };
	

	int LError(const char* fmt, ...) const
	{
		/* Sorry about this */
		constexpr size_t BuffSz = 512; /* short_src[256], shouldn't be a problem */
		char TraceStr[BuffSz]{};
		char ErrStr[BuffSz]{};
		char FinalStr[(BuffSz * 2) + 1]{};
		va_list argp;
		va_start(argp, fmt);
		/*  luaL_where(L, 1); */
		/* --- luaL_where --- */
		int level = 1;
		lua_Debug ar;
		if (GetStack(level, &ar)) {  /* check function at level */
			GetInfo("Sl", &ar);  /* get info about it */
			if (ar.currentline > 0) {  /* is there info? */
				sprintf_s(TraceStr, "%s:%d: ", ar.short_src, ar.currentline);
			}
		}
		{} /* else, no information available... */
		/* --- luaL_where --- */
		vsnprintf(ErrStr, BuffSz, fmt, argp);
		va_end(argp);
		strcpy_s(FinalStr, TraceStr);
		strcat_s(FinalStr, ErrStr);
		PushString(FinalStr);
		return Error();
	}
	int ArgError(int narg, const char* extramsg) const
	{
		lua_Debug ar;
		if (!GetStack(0, &ar))  /* no stack frame? */
			return LError("bad argument #%d (%s)", narg, extramsg);
		GetInfo("n", &ar);
		if (strcmp(ar.namewhat, "method") == 0) {
			narg--;  /* do not count `self' */
			if (narg == 0)  /* error is in the self argument itself? */
				return LError("calling " LUA_QS " on bad self (%s)",
					ar.name, extramsg);
		}
		if (ar.name == NULL)
			ar.name = "?";
		return LError("bad argument #%d to " LUA_QS " (%s)",
			narg, ar.name, extramsg);
	}
	
};

#endif // LUAVM_H
