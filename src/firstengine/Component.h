#ifndef FIRSTENGINE_COMPONENT_H
#define FIRSTENGINE_COMPONENT_H
#include <memory>


namespace firstengine
{
	struct Core;
	struct Entity;
	struct Transform;
	/********************************************//**
	*  \brief Allows for functionality to be added to Entity
	***********************************************/
	struct Component
	{
		friend struct firstengine::Entity;
		/********************************************//**
		*  \brief Function called upon a component being created
		***********************************************/
		void onInitialize() {};
		/********************************************//**
		*  \brief Function called every tick, used to call onTick
		***********************************************/
		void tick();
		/********************************************//**
		*  \brief Function to be overidden with specific component commands 
		***********************************************/
		virtual void onTick();
		/********************************************//**
		*  \brief Function called every tick, used to call onRender
		***********************************************/
		void render();
		/********************************************//**
		*  \brief Function to be overidden with any rendering information
		***********************************************/
		virtual void onRender();
		/********************************************//**
		*  \brief Function called when a component has gone out of scope
		***********************************************/
		void destroy();
		/********************************************//**
		*  \brief Function to be overidden with anything that should happen on destory (E.G : Cleanup )
		***********************************************/
		virtual void onDestroy();
		/********************************************//**
		* \brief Returns pointer to Core
		***********************************************/
		std::shared_ptr<Core> getCore();
		/********************************************//**
		* \brief Returns pointer to Entity
		***********************************************/
		std::shared_ptr<Entity> getEntity();
		/********************************************//**
		* \brief Shortcut for getting the parent entities transform
		***********************************************/
		std::shared_ptr<Transform> getTransform();



	private:
		std::weak_ptr<Entity> entity;

	};
}
#endif
