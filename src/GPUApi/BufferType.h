#pragma once
#ifndef BUFFER_TYPE_H
#define BUFFER_TYPE_H
#include "../Utils/Types.h"
#include "GL/GL.h"

namespace gfm {
namespace INTERNAL {
namespace gpu {

	enum class BufferType {
		eVERTEX = GL_ARRAY_BUFFER,
		eINDEX = GL_ELEMENT_ARRAY_BUFFER,
		eUNIFORM = GL_UNIFORM_BUFFER
	};

}//INTERNAL
}//graphic
}//gfm
#endif // BUFFER_TYPE_H