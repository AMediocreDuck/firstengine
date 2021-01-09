#ifndef FIRSTENGINE_ENTITY_H
#define FIRSTENGINE_ENTITY_H

#include "firstengine/Exception.h"
#include <vector>
#include <memory>
#include "Transform.h"
#include "Camera.h"


namespace firstengine
{
	struct Exception;
	struct Component;
	struct Core;
	/********************************************//**
	* \brief Allows for game objects to be created
	***********************************************/
	struct Entity
	{
		friend struct firstengine::Core;
		/********************************************//**
		* \brief Template function that adds a Component of any type to an Entity
		***********************************************/
		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();
			rtn->entity = self;
			components.push_back(rtn);

			rtn->onInitialize();
			return rtn;
		}
		/********************************************//**
		* \brief Template function that allows an unspecified amount of parameters to be passed in while adding a component
		***********************************************/
		template <typename T, typename ...Args>
		std::shared_ptr<T> addComponent(Args&&... args)
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();
			rtn->entity = self;
			components.push_back(rtn);

			rtn->onInitialize(std::forward<Args>(args)...);
			return rtn;
		}
		/********************************************//**
		* \brief Tick is called once a frame and is used to call all the Entity Component ticks
		***********************************************/
		void tick();
		/********************************************//**
		* \brief Tick is called once a frame after all Entity have performed tick()
		***********************************************/
		void afterTick();
		/********************************************//**
		* \brief Runs through and calls all component Render functions 
		***********************************************/
		void render();
		/********************************************//**
		* \brief Returns a pointer to Core
		***********************************************/
		std::shared_ptr<Core> getCore();
		/********************************************//**
		* \brief Returns pointer to a specified Component if one is found
		***********************************************/
		template <typename T>
		std::shared_ptr<T> getComponent()
		{
			for (size_t ci = 0; ci < components.size(); ci++)
			{
				std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(components.at(ci));
				if (rtn)
				{
					return rtn;
				}
			}
			throw firstengine::Exception("Requested component was not found");
		}
	private:
		std::vector<std::shared_ptr<Component>> components;
		std::weak_ptr<Core> core;
		std::weak_ptr<Entity> self;

	};
}
#endif
