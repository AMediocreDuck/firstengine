#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#ifndef FIRSTENGINE_CORE_H
#define FIRSTENGINE_CORE_H


#include <memory> 
#include <vector>
#include <fegraphics/fegraphics.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <AL/al.h>
#include <AL/alc.h>


namespace firstengine
{
	struct Context;
	struct CacheManager;
	struct Entity;
	struct Screen;
	struct Keyboard;

	struct Camera;
	struct Core
	{
		/********************************************//**
		* \brief Cleans up after program ends
		***********************************************/
		~Core();
		/********************************************//**
		* \brief Sets up program and creates a pointer to Core
		***********************************************/
		static std::shared_ptr<Core> initialize();
		/********************************************//**
		* \brief Creates and adds an Entity to cores local Entity storage
		***********************************************/
		std::shared_ptr<Entity> addEntity();
		/********************************************//**
		* \brief Creates and adds a Camera Entity to cores local Camera storage
		***********************************************/
		std::shared_ptr<Entity> addCamera();
		/********************************************//**
		* \brief Starts the main programs loop
		***********************************************/
		void start();
		/********************************************//**
		* \brief Returns pointer to the Screen
		***********************************************/
		std::shared_ptr<Screen> getScreen();
		/********************************************//**
		* \brief Returns pointer to the Keyboard
		***********************************************/
		std::shared_ptr<Keyboard> getKeyboard();

		//SDL_Window* window;
		//SDL_GLContext glContext;
		/********************************************//**
		* \brief Variable to keep track of whether or not sound is supported
		***********************************************/
		bool soundWorking;
		/********************************************//**
		* \brief Gateway to the graphics library
		***********************************************/
		std::shared_ptr<fegraphics::Context> context;
		/********************************************//**
		* \brief Returns the currently active Camera
		***********************************************/
		std::shared_ptr<Camera> getActiveCamera() { return activeCamera; }
		/********************************************//**
		* \brief Store of all resources that have been loaded
		***********************************************/
		std::shared_ptr<CacheManager> cacheManager;

	private:
#ifdef EMSCRIPTEN
		static bool Loop();
#else 
		bool Loop();
#endif
		void setActiveCamera(std::shared_ptr<Camera> _activeCamera) { activeCamera = _activeCamera; }
		SDL_Window* window;
		SDL_GLContext glContext;
		ALCdevice* alDevice;
		ALCcontext* alContext;

		std::vector<std::shared_ptr<Entity>> entities;
		std::vector<std::shared_ptr<Entity>> cameras;
		std::shared_ptr<Camera> activeCamera;
		std::shared_ptr<Screen> screen;
		std::shared_ptr<Keyboard> keyboard;
		std::weak_ptr<Core> self;

	};
}
#endif