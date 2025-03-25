@echo off
set param1=%~1
set param2=%~2

if "%param2%" == "clean" (
    rmdir /s /q LGExtender.dir
    rmdir /s /q LGExtenderLib.dir
)

cmake .
cmake --build . 

if "%param1%" == "run" (
    @REM "F:\Developpement\C++\hacklib\bin64\ldr.exe" -pname lghub_agent.exe -lib F:\Developpement\C++\lgpro\Debug\LGProLib.dll 
    "./Debug/launcher.exe"
)