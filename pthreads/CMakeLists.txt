cmake_minimum_required (VERSION 3.14)
project(hw4)

#set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra -Wshadow -Werror -D_XOPEN_SOURCE=500")
#set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wshadow -Werror -Wno-sign-compare -D_XOPEN_SOURCE=500")

set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra -Wshadow -Werror")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wshadow -Werror")

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(pthread_main pthreads/pthread_main.c)

# make an executable
add_executable(${PROJECT_NAME}_test pthreads/pthread_main.c)
target_compile_definitions(${PROJECT_NAME}_test PRIVATE)
target_link_libraries(${PROJECT_NAME}_test gtest pthread phtread_main)

