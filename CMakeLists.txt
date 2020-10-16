cmake_minimum_required(VERSION 3.14)
project(k2tree-dyn)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_FLAGS "-Wall -Wextra -std=c99 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -Werror")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++17 -pedantic -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


include_directories(include)

enable_testing()



option(WITH_EXAMPLES "With Examples" ON)


if(WITH_EXAMPLES)
add_executable(example1 example/example1.c example/intvector.c)
add_executable(measure_insert example/measure_insert.cpp example/intvector.c)
endif()


find_package(GTest QUIET)
if(GTest_FOUND)
include_directories(${GTEST_INCLUDE_DIRS})


add_executable(vector_test test/vector_test.cpp)
target_link_libraries(vector_test ${GTEST_BOTH_LIBRARIES} pthread )


add_test(NAME vector_test COMMAND ./vector_test)
endif()