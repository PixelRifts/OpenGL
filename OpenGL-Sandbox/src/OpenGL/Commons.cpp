#include "Commons.h"

namespace OpenGL {
	// Returns the base type of the datatype (float for matrices)
	GLenum GetBaseType(Datatype type)
	{
		switch (type) {
		case Datatype::Float: return GL_FLOAT;
		case Datatype::Float2: return GL_FLOAT;
		case Datatype::Float3: return GL_FLOAT;
		case Datatype::Float4: return GL_FLOAT;
		case Datatype::Int: return GL_INT;
		case Datatype::Int2: return GL_INT;
		case Datatype::Int3: return GL_INT;
		case Datatype::Int4: return GL_INT;
		case Datatype::Matrix3: return GL_FLOAT;
		case Datatype::Matrix4: return GL_FLOAT;
		}

		return GL_INVALID_ENUM;
	}

	// Returns size of one instance of a datatype
	int GetSize(Datatype type)
	{
		switch (type) {
		case Datatype::Float: return 1 * sizeof(float);
		case Datatype::Float2: return 2 * sizeof(float);
		case Datatype::Float3: return 3 * sizeof(float);
		case Datatype::Float4: return 4 * sizeof(float);
		case Datatype::Int: return 1 * sizeof(int);
		case Datatype::Int2: return 2 * sizeof(int);
		case Datatype::Int3: return 3 * sizeof(int);
		case Datatype::Int4: return 4 * sizeof(int);
		case Datatype::Matrix3: return 3 * 3 * sizeof(float);
		case Datatype::Matrix4: return 4 * 4 * sizeof(float);
		}

		return -1;
	}

	// Returns number of elements of base type in this datatype
	int GetElementCount(Datatype type)
	{
		switch (type) {
		case Datatype::Float: return 1;
		case Datatype::Float2: return 2;
		case Datatype::Float3: return 3;
		case Datatype::Float4: return 4;
		case Datatype::Int: return 1;
		case Datatype::Int2: return 2;
		case Datatype::Int3: return 3;
		case Datatype::Int4: return 4;
		case Datatype::Matrix3: return 3 * 3;
		case Datatype::Matrix4: return 4 * 4;
		}

		return -1;
	}
}