cmake_minimum_required(VERSION 3.0.0)
project(Pwn3 VERSION 0.1.0)

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
