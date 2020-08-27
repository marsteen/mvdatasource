cmake_minimum_required(VERSION 3.10)
project(mvdatasource)

include_directories(./include)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")

add_executable(mvdatasource
    main.cpp
    ./lib/CFileIO.cpp
    ./lib/NStringTool.cpp
)


