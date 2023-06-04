cmake_minimum_required(VERSION 3.0.0)
project(Pwn3 VERSION 0.1.0)

include(FetchContent)
set(BUILD_SHARED_LIBS  OFF)
FetchContent_Declare(
    SDL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG        v2.26.5
)
FetchContent_MakeAvailable(SDL)

include(CTest)
enable_testing()

file(GLOB src
     "src/**.h"
     "src/**.cpp"
)

add_library(Pwn3 SHARED src/main.cpp ${src})
set_target_properties(Pwn3 PROPERTIES OUTPUT_NAME "injection")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
