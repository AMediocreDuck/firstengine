#ifndef FIRSTENGINE_MODEL_H
#define FIRSTENGINE_MODEL_H

#include <memory>
#include <GL/glew.h>
#include "Resource.h"
#include "fegraphics/Model.h"

namespace firstengine
{
	struct Renderer;
	/********************************************//**
	*  \brief Wrapper Class for the Model Resource
	***********************************************/
	struct Model : public Resource
	{
		/********************************************//**
		*  \brief Loads the appropriate data for the Resource to be used
		***********************************************/
		void onLoad();
	private:
		friend struct firstengine::Renderer;
		std::shared_ptr<fegraphics::Model> fegModel;
	};
}



#endif
