cmake_minimum_required(VERSION 3.21)
project(HomelessProgram)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(${PROJECT_SOURCE_DIR}/ThirdParty/libmem)

include_directories(${PROJECT_SOURCE_DIR}/ThirdParty/libmem/libmem)

file(GLOB_RECURSE HEADERS_FILES
        ${PROJECT_SOURCE_DIR}/Headers/*.hpp
        ${PROJECT_SOURCE_DIR}/Headers/*.h
        ${PROJECT_SOURCE_DIR}/Headers/*.inl
        )
file(GLOB_RECURSE SOURCES_FILES
        ${PROJECT_SOURCE_DIR}/Sources/*.cpp
        ${PROJECT_SOURCE_DIR}/Sources/*.c
        )


SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Bin)

include_directories(${PROJECT_SOURCE_DIR}/Lib/)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/Lib/)

add_executable(HomelessProgram main.cpp ${SOURCES_FILES} ${HEADERS_FILES} ${PROJECT_SOURCE_DIR}/ThirdParty/libmem/libmem/libmem.c)
