namespace logi
{
    namespace scripting
    {
        namespace lua
        {
            class LuaVirtualMachine
            {
            public:

                virtual void unk0() = 0;
                virtual void unk1() = 0;
                virtual void unk2() = 0;
                virtual void unk3() = 0;
            
                char pad_0x0000[0x30]; //0x0000
                void* luaState; //0x0030
            };
        } // namespace lua
        
    } // namespace scripting
    
} // namespace logi