cmake_minimum_required(VERSION 3.10)
project(SDL_gpu C)

set(SDL_gpu_src
	${SDL_gpu_src}
	src/SDL_gpu.c
	src/SDL_gpu_matrix.c
	src/SDL_gpu_renderer.c
	src/SDL_gpu_shapes.c
	src/renderer_OpenGL_1_BASE.c
	src/renderer_OpenGL_1.c
	src/renderer_OpenGL_2.c
	src/renderer_OpenGL_3.c
	src/renderer_OpenGL_4.c
	src/renderer_GLES_1.c
	src/renderer_GLES_2.c
	src/renderer_GLES_3.c
	src/externals/stb_image/stb_image.c
	src/externals/stb_image_write/stb_image_write.c
	src/externals/glew/glew.c
	)

add_library(SDL_gpu STATIC ${SDL_gpu_src})
target_compile_definitions(SDL_gpu PUBLIC "SDL_GPU_DISABLE_GLES")
target_include_directories(SDL_gpu PRIVATE include/ src/externals/stb_image src/externals/stb_image_write src/externals/glew/GL src/externals/glew/ src/)
target_include_directories(SDL_gpu PUBLIC include/)
target_link_libraries(SDL_gpu SDL2::SDL2)
set_target_properties(SDL_gpu PROPERTIES C_STANDARD 99 LINKER_LANGUAGE C)
	


