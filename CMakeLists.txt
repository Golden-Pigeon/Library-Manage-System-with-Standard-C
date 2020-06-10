cmake_minimum_required(VERSION 3.15)
project(library C)

set(CMAKE_C_STANDARD 99)

add_executable(library main.c util/hash_map.h util/hash.h core/book.h core/lbr.h core/user.h main.h util/hash_map.c util/my_math.c util/my_math.h util/hash.c core/book.c core/user.c util/list.c util/list_user.h util/list_book.h util/my_string.c util/my_string.h core/lbr.c)