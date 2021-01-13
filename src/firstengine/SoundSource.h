#ifndef FIRSTENGINE_SOUNDSOURCE_H
#define FIRSTENGINE_SOUNDSOURCE_H


#include "Component.h"
#include <memory>
#include <AL/al.h>

namespace firstengine
{
	struct Sound;
	/********************************************//**
	* \brief Component to play music 
	***********************************************/
	struct SoundSource : public Component
	{
		/********************************************//**
		* \brief Called on creation
		***********************************************/
		void onInitialize();
		/********************************************//**
		* \brief Called every frame
		***********************************************/
		void onTick();
		/********************************************//**
		* \brief Called when object is destroyed or out of scope 
		***********************************************/
		void onDestroy();
		/********************************************//**
		* \brief Sets the sound that will play
		***********************************************/
		void setSound(const char* path);
	private:
		bool soundWorking;
		std::shared_ptr<Sound> sound;
		ALuint ssId;

	};
}


#endif