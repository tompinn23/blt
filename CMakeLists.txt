cmake_minimum_required(VERSION 3.10)

project(blt CXX)

option(BLT_BUILD_STATIC "Build Static Library" OFF)
option(BLT_BUILD_SHARED "Build Shared LibrarY" ON)

set(BLT_SRC src/blt.cpp)


if(BLT_BUILD_STATIC)
	add_library(blt-static STATIC ${BLT_SRC})
	target_include_directories(blt-static PUBLIC include)
	target_compile_definitions(blt-static PUBLIC BLT_BUILD_STATIC)
endif()

if(BLT_BUILD_SHARED)
	add_library(blt SHARED ${BLT_SRC})	
	target_include_directories(blt PUBLIC include)
	target_compile_definitions(blt PUBLIC BLT_BUILDING_LIB)
endif()

add_executable(test src/test.cpp)
target_link_libraries(test blt)
