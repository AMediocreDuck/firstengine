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
		*  \brief Tick ran before all other Ticks
		***********************************************/
		void speedTick();
		/********************************************//**
		*  \brief Tick ran before all other Ticks
		***********************************************/
		virtual void onSpeedTick();
		/********************************************//**
		*  \brief Function called every tick, used to call onTick
		***********************************************/
		void tick();
		/********************************************//**
		*  \brief Function to be overidden with specific component commands 
		***********************************************/
		virtual void onTick();
		/********************************************//**
		*  \brief Calls onAfterTick() after all other ticks have happened
		***********************************************/
		virtual void afterTick();
		/********************************************//**
		*  \brief Tick called after all other tick() have ran
		***********************************************/
		virtual void onAfterTick();

		/********************************************//**
		*  \brief Function called anytime a Collision is detected
		***********************************************/
		virtual void onCollision(std::shared_ptr<Entity> Collision);
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
