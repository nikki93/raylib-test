cmake_minimum_required(VERSION 3.16)

# Web toolchain
if(WEB)
  set(CMAKE_TOOLCHAIN_FILE ../emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake)
  set(CMAKE_EXE_LINKER_FLAGS "-s WASM=1 -s ASSERTIONS=1 -s MAX_WEBGL_VERSION=2 -s TOTAL_MEMORY=32MB -s ALLOW_MEMORY_GROWTH=1")
endif()


# Project
project(raylib-test)
set(MY_LIBRARIES "")


# Generate 'compile_commands.json'
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Release build by default
set(CMAKE_BUILD_TYPE Release)


# raylib
if(WEB)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3")
  set(PLATFORM "Web" CACHE STRING "" FORCE)
endif()
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/raylib)
list(APPEND MY_LIBRARIES "raylib")


# fmt
add_subdirectory(vendor/fmt)
include_directories(${PROJECT_SOURCE_DIR}/vendor/fmt/include)
list(APPEND MY_LIBRARIES "fmt::fmt")


# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Main executable
add_executable(raylib-test main.cc)
target_link_libraries(raylib-test "${MY_LIBRARIES}")
if(WEB)
  configure_file(${PROJECT_SOURCE_DIR}/index.html index.html)
endif()
