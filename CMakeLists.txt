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

add_library(fegraphics
src/fegraphics/ShaderProgram.cpp
src/fegraphics/Texture.cpp
src/fegraphics/Model.cpp
src/fegraphics/Context.cpp
src/fegraphics/Exception.cpp
src/fegraphics/bugl.h
src/fegraphics/fegraphics.h


src/fegraphics/ShaderProgram.h
src/fegraphics/Texture.h
src/fegraphics/Model.h
src/fegraphics/Context.h
src/fegraphics/Exception.h


)
# .h file included to show in VS
add_library(firstengine
src/firstengine/Core.cpp
src/firstengine/Entity.cpp
src/firstengine/Component.cpp
src/firstengine/Exception.cpp
src/firstengine/Renderer.cpp
src/firstengine/Transform.cpp
src/firstengine/Screen.cpp
src/firstengine/Keyboard.cpp
src/firstengine/Resource.cpp
src/firstengine/CacheManager.cpp
src/firstengine/Sound.cpp
src/firstengine/SoundSource.cpp
src/firstengine/Texture.cpp
src/firstengine/Model.cpp
src/firstengine/vShader.cpp
src/firstengine/fShader.cpp

src/firstengine/Core.h
src/firstengine/Entity.h
src/firstengine/Component.h
src/firstengine/firstEngine.h
src/firstengine/Exception.h
src/firstengine/Renderer.h
src/firstengine/Transform.h
src/firstengine/Screen.h
src/firstengine/Keyboard.h
src/firstengine/Resource.h
src/firstengine/CacheManager.h
src/firstengine/Sound.h
src/firstengine/SoundSource.h
src/firstengine/Texture.h
src/firstengine/Model.h
src/firstengine/vShader.h
src/firstengine/fShader.h
)

if(MSVC OR MINGW)
	target_link_libraries(fegraphics SDL2 glew32 opengl32)
	target_link_libraries(firstengine fegraphics SDL2 glew32 OpenAL32)

else()
	target_link_libraries(fegraphics SDL2 GLEW GL)
	target_link_libraries(firstengine fegraphics SDL2 GLEW OpenAL32)
endif()

add_executable(demo
src/demo/main.cpp
)

target_link_libraries(demo firstengine)



