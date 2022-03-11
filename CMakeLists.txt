cmake_minimum_required(VERSION 3.17)
project(math C)

set(CMAKE_C_STANDARD 99)

add_executable(math main.c util/BigInteger.h util/BigInteger.c)