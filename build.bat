@echo off
set param1=%~1
set param2=%~2

if "%param2%" == "clean" (
    rmdir /s /q LGPro.dir
    rmdir /s /q LGProLib.dir
)

cmake .
cmake --build . 

if "%param1%" == "run" (
    "F:\Developpement\C++\hacklib\bin64\ldr.exe" -pname lghub_agent.exe -lib F:\Developpement\C++\lgpro\Debug\LGProLib.dll 
)