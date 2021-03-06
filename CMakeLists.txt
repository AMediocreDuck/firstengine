cmake_minimum_required(VERSION 2.6)
project(FIRSTENGINE)

add_definitions(-DSDL_MAIN_HANDLED)


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

add_library(fenet
src/fenet/Exception.cpp
src/fenet/IPEndPoint.cpp
src/fenet/Network.cpp
src/fenet/Packet.cpp
src/fenet/Socket.cpp
src/fenet/SslSocket.cpp

src/fenet/Constants.h
src/fenet/Exception.h
src/fenet/Fenet.h
src/fenet/FenetResult.h
src/fenet/IPVersion.h
src/fenet/IPEndPoint.h
src/fenet/Network.h
src/fenet/Packet.h
src/fenet/Socket.h
src/fenet/SocketHandle.h
src/fenet/SocketOptions.h
src/fenet/SslSocket.h
)

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

add_library(fephysics
src/fephysics/BasicNewtonianPhysics.cpp
src/fephysics/CollisionDetection.cpp
src/fephysics/DynamicObject.cpp
src/fephysics/GameObject.cpp
src/fephysics/Geometry.cpp
src/fephysics/GeometryVolume.cpp
src/fephysics/KinematicEquations.cpp
src/fephysics/Projectile.cpp
src/fephysics/VectorMath.cpp
src/fephysics/VelocityAcceleration.cpp
src/fephysics/fephysics.h

src/fephysics/BasicNewtonianPhysics.h
src/fephysics/CollisionDetection.h
src/fephysics/DynamicObject.h
src/fephysics/GameObject.h
src/fephysics/Geometry.h
src/fephysics/GeometryVolume.h
src/fephysics/KinematicEquations.h
src/fephysics/Projectile.h
src/fephysics/VectorMath.h
src/fephysics/VelocityAcceleration.h
)
# .h file included to show in VS
add_library(firstengine
src/firstengine/CacheManager.cpp
src/firstengine/Camera.cpp
src/firstengine/Collider.cpp
src/firstengine/Component.cpp
src/firstengine/Core.cpp
src/firstengine/Entity.cpp
src/firstengine/Exception.cpp
src/firstengine/fShader.cpp
src/firstengine/Keyboard.cpp
src/firstengine/Model.cpp
src/firstengine/NetworkManager.cpp
src/firstengine/Packet.cpp
src/firstengine/Renderer.cpp
src/firstengine/Resource.cpp
src/firstengine/RigidBody.cpp
src/firstengine/Screen.cpp
src/firstengine/Shader.cpp
src/firstengine/Socket.cpp
src/firstengine/Sound.cpp
src/firstengine/SoundSource.cpp
src/firstengine/SphereCollider.cpp
src/firstengine/Texture.cpp
src/firstengine/ThreadManager.cpp
src/firstengine/Transform.cpp
src/firstengine/vShader.cpp

src/firstengine/firstEngine.h
src/firstengine/CacheManager.h
src/firstengine/Camera.h
src/firstengine/Collider.h
src/firstengine/Component.h
src/firstengine/Core.h
src/firstengine/Entity.h
src/firstengine/Exception.h
src/firstengine/fShader.h
src/firstengine/Keyboard.h
src/firstengine/Model.h
src/firstengine/NetworkManager.h
src/firstengine/Packet.h
src/firstengine/Renderer.h
src/firstengine/Resource.h
src/firstengine/RigidBody.h
src/firstengine/Screen.h
src/firstengine/Shader.h
src/firstengine/Socket.h
src/firstengine/Sound.h
src/firstengine/SoundSource.h
src/firstengine/SphereCollider.h
src/firstengine/Texture.h
src/firstengine/ThreadManager.h
src/firstengine/Transform.h
src/firstengine/vShader.h

)

if(MSVC OR MINGW)
	target_link_libraries(fenet Ws2_32.lib libssl.lib libcrypto.lib)
	target_link_libraries(fephysics glew32 opengl32)
	target_link_libraries(firstengine fegraphics fephysics fenet SDL2 glew32 OpenAL32)

else()
	target_link_libraries(fephysics GLEW GL)
	target_link_libraries(fegraphics SDL2 GLEW GL)
	target_link_libraries(firstengine fegraphics fephysics fenet SDL2 GLEW OpenAL32)
endif()

add_executable(demoClient
src/demoClient/main.cpp
)
add_executable(demoServer
src/demoServer/main.cpp
)

target_link_libraries(demoClient firstengine)
target_link_libraries(demoServer firstengine)



