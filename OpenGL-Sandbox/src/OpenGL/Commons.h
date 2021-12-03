#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>

namespace OpenGL {
	enum Datatype {
		Float,   // float
		Float2,  // vec2
		Float3,  // vec3
		Float4,  // vec4
		Int,     // int
		Int2,    // ivec2
		Int3,    // ivec3
		Int4,    // ivec4
		Matrix3, // mat3
		Matrix4, // mat4
	};

	GLenum GetBaseType(Datatype type);
	int GetSize(Datatype type);
	int GetElementCount(Datatype type);
}