cmake_minimum_required(VERSION 2.6)
project(FIRSTENGINE)

add_definitions(-DSDL_MAIN_HANDLED)

include_directories(
src
)

if(MSVC)
	include_directories(
		${PROJECT_SOURCE_DIR}/contrib/msvc-windows-x86_64/include
	)
	link_directories(
		${PROJECT_SOURCE_DIR}/contrib/msvc-windows-x86_64/lib
	)
endif()



add_library(rend
  src/rend/Exception.cpp
  src/rend/Context.cpp
  src/rend/Texture.cpp
  src/rend/RenderTexture.cpp
  src/rend/Shader.cpp
  src/rend/Buffer.cpp
  src/rend/Mesh.cpp
  src/rend/Util.cpp
)
if(MSVC OR MINGW)
  target_link_libraries(rend SDL2 glew32 opengl32)
else()
  target_link_libraries(rend SDL2 GLEW GL)
endif()

# .h file included to show in VS
add_library(firstengine
src/firstengine/Core.cpp
src/firstengine/Entity.cpp
src/firstengine/Component.cpp
src/firstengine/Exception.cpp
src/firstengine/Renderer.cpp
src/firstengine/Core.h
src/firstengine/Entity.h
src/firstengine/Component.h
src/firstengine/firstEngine.h
src/firstengine/Exception.h
src/firstengine/Renderer.h
)

add_executable(demo
src/demo/main.cpp
)

target_link_libraries(demo firstengine)
target_link_libraries(firstengine rend SDL2 glew32)


