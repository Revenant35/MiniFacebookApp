cmake_minimum_required(VERSION 3.21)
project(Programming_Assignment_1 C)

set(CMAKE_C_STANDARD 99)

add_executable(Programming_Assignment_1 main.c Hash.c Hash.h Utility.c Utility.h Node.c Node.h friends.c friends.h)
#add_executable(Programming_Assignment_1 test.c Node.c friends.c)