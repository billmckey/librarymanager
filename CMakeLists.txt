cmake_minimum_required(VERSION 3.10)
project(LibraryManagement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(library_manager
    src/main.cpp
    src/Book.cpp
    src/Library.cpp
    src/User.cpp
)

target_include_directories(library_manager PRIVATE src)