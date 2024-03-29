cmake_minimum_required(VERSION 3.10)

project(blt CXX)

option(BLT_BUILD_STATIC "Build Static Library" OFF)
option(BLT_BUILD_SHARED "Build Shared LibrarY" ON)

set(BLT_SRC src/blt.cpp src/Options.cpp src/OptionGroup.cpp src/Console.cpp src/log.cc)

# Handle SDL2

#set(SDL_LINK_STATIC ON)
#set(SDL_SHARED OFF)
add_subdirectory(deps/SDL2-2.0.9)
add_subdirectory(deps/sdl-gpu)
#add_subdirectory(deps/libiconv-1.16)
add_subdirectory(deps/fmt)




if(BLT_BUILD_STATIC)
	add_library(blt-static STATIC ${BLT_SRC})
	target_include_directories(blt-static PUBLIC include)
	target_compile_definitions(blt-static PUBLIC BLT_BUILD_STATIC)
	target_link_libraries(blt-static SDL2 SDL2main SDL_gpu)
endif()

if(BLT_BUILD_SHARED)
	add_library(blt SHARED ${BLT_SRC})	
	target_include_directories(blt PUBLIC include)
	target_compile_definitions(blt PUBLIC BLT_BUILDING_LIB)
	target_link_libraries(blt SDL2 SDL2main SDL_gpu fmt)
endif()

add_executable(test src/test.cpp)
target_link_libraries(test blt)
