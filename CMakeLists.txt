cmake_minimum_required(VERSION 3.5)
project(LGPro)
project(LGProLib)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Add the executable
# add_executable(LGPro src/bin/main.cpp)

file(GLOB MINHOOK_SOURCES "src/lib/minhook/**/*.c" "src/lib/minhook/*.c")
file(GLOB MINHOOK_HEADERS "src/lib/minhook/**/*.h" "src/lib/minhook/*.h")
file(GLOB SDK "src/lib/sdk/**/*.h" "src/lib/sdk/*.h")
file(GLOB LUA "src/lib/lua/*.h" "src/lib/lua/*.c")
file(GLOB HOOKS "src/lib/hooks/*.h" "src/lib/hooks/*.cpp")

add_library(LGProLib SHARED
    src/lib/main.cpp
    src/lib/PatternScanner.h

    ${SDK}
    ${LUA}
    ${HOOKS}
    
    ${MINHOOK_SOURCES}
    ${MINHOOK_HEADERS}
)

target_include_directories(${PROJECT_NAME} PRIVATE src/lib)
