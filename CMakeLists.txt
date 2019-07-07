cmake_minimum_required(VERSION 3.10)

project(blt CXX)

option(BLT_BUILD_STATIC "Build Static Library" OFF)
option(BLT_BUILD_SHARED "Build Shared LibrarY" ON)

set(BLT_SRC src/blt.cpp)

# Handle SDL2

#if(MINGW OR NOT WIN32)
	#message(STATUS "Building in MingW")
	find_package(SDL2)
	if(NOT SDL2_FOUND)
		add_subdirectory(deps/SDL2-2.0.9)
	else()
		message(STATUS "SDL2 INCLUDE DIRS: ${SDL2_INCLUDE_DIRS}")
		if(TARGET SDL2::SDL2)

		else()
			add_library(SDL2::SDL2 INTERFACE)
			target_include_directories(SDL2::SDL2 INTERFACE ${SDL2_INCLUDE_DIRS})
			target_link_libraries(SDL2::SDL2 INTERFACE ${SDL2_LIBRARIES})
		endif()
	endif()
#endif()


add_subdirectory(deps/sdl-gpu)


if(BLT_BUILD_STATIC)
	add_library(blt-static STATIC ${BLT_SRC})
	target_include_directories(blt-static PUBLIC include)
	target_compile_definitions(blt-static PUBLIC BLT_BUILD_STATIC)
	target_link_libraries(blt-static SDL2::SDL2 SDL_gpu)
endif()

if(BLT_BUILD_SHARED)
	add_library(blt SHARED ${BLT_SRC})	
	target_include_directories(blt PUBLIC include)
	target_compile_definitions(blt PUBLIC BLT_BUILDING_LIB)
	target_link_libraries(blt SDL2::SDL2 SDL_gpu)
endif()

add_executable(test src/test.cpp)
target_link_libraries(test blt)
