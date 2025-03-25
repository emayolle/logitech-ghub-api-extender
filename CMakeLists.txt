cmake_minimum_required(VERSION 3.5)
project(LGExtender)
project(LGExtenderLib)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Set the output directory for executables and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Add the executable with a custom name
add_executable(LGExtender src/app/main.cpp)
set_target_properties(LGExtender PROPERTIES OUTPUT_NAME "launcher")

file(GLOB MINHOOK_SOURCES "src/lib/minhook/**/*.c" "src/lib/minhook/*.c")
file(GLOB MINHOOK_HEADERS "src/lib/minhook/**/*.h" "src/lib/minhook/*.h")
file(GLOB SDK "src/lib/sdk/**/*.h" "src/lib/sdk/*.h")
file(GLOB LUA "src/lib/lua/*.h" "src/lib/lua/*.c")
file(GLOB HOOKS "src/lib/hooks/*.h" "src/lib/hooks/*.cpp")

add_library(LGExtenderLib SHARED
    src/lib/main.cpp
    src/lib/PatternScanner.h

    ${SDK}
    ${LUA}
    ${HOOKS}
    
    ${MINHOOK_SOURCES}
    ${MINHOOK_HEADERS}
)
set_target_properties(LGExtenderLib PROPERTIES OUTPUT_NAME "lgextender")

target_include_directories(${PROJECT_NAME} PRIVATE src/lib)
