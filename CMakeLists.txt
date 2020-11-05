cmake_minimum_required(VERSION 2.6)
project(FIRSTENGINE)

add_definitions(-DSDL_MAIN_HANDLED)
set(CMAKE_EXECUTABLE_SUFFIX ".html")

include_directories(
src
)

if(MSVC)
	include_directories(
		${PROJECT_SOURCE_DIR}/contrib/msvc-windows-x86_64/include)
	link_directories(
		${PROJECT_SOURCE_DIR}/contrib/msvc-windows-x86_64/lib
	)
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s DISABLE_EXCEPTION_CATCHING=0")
endif()


# .h file included to show in VS
add_library(firstengine
src/firstengine/Core.cpp
src/firstengine/Entity.cpp
src/firstengine/Component.cpp
src/firstengine/Exception.cpp
src/firstengine/Renderer.cpp
src/firstengine/Transform.cpp
src/firstengine/Screen.cpp
src/firstengine/ShaderProgram.cpp
src/firstengine/Texture.cpp
src/firstengine/Model.cpp
src/firstengine/Context.cpp
src/firstengine/Resource.cpp
src/firstengine/CacheManager.cpp
src/firstengine/vShader.cpp
src/firstengine/fShader.cpp
src/firstengine/bugl.h
src/firstengine/Core.h
src/firstengine/Entity.h
src/firstengine/Component.h
src/firstengine/firstEngine.h
src/firstengine/Exception.h
src/firstengine/Renderer.h
src/firstengine/Transform.h
src/firstengine/Screen.h
src/firstengine/ShaderProgram.h
src/firstengine/Texture.h
src/firstengine/Model.h
src/firstengine/Context.h
src/firstengine/Resource.h
src/firstengine/CacheManager.h
src/firstengine/vShader.h
src/firstengine/fShader.h
)

if(MSVC OR MINGW)
	target_link_libraries(firstengine SDL2 glew32 opengl32)
else()
	target_link_libraries(firstengine SDL2 GLEW GL)
endif()

add_executable(demo
src/demo/main.cpp
)

target_link_libraries(demo firstengine)



