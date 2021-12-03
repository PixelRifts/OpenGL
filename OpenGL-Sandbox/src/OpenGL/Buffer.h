#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>

namespace OpenGL {
	// IMatrix not supported. generally not required
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

	class BufferAttribute {
	public:
		BufferAttribute(std::string name, Datatype type); // Name technically not required

		std::string Name;
		Datatype Type;
		uint32_t Offset;
	};

	// A Buffer can hold multiple "Attributes" (Technically a Vertex Array Term) that are packed together
	// For example: a buffer which has 2 attributes (pos: vec2, uv: vec2) would look something like this:
	// [ vertex1.pos.x, vertex1.pos.y, vertex1.uv.x, vertex1.uv.y, vertex2.pos.x, ... ]
	// Its stride would be the sum of all the sizes of attributes. Here: sizeof(vec2) + sizeof(vec2)
	// Offset of each of these attributes would be the offset in bytes from the start of the vertex.
	// So here [ { vertex1.pos.x, vertex1.pos.y }, { vertex1.uv.x, vertex1.uv.y }, vertex2.pos.x, ... ]
	//           ^                                 ^
	//           ^ attribute "pos" starts at 0     ^ attribute "uv" starts at 0 + sizeof(pos attribute) and so on.
	class VertexBuffer {
	public:
		// Creates the buffer. Doesn't allocate any data
		VertexBuffer(std::initializer_list<BufferAttribute> attribs);
		// Creates the buffer. Allocates data with "size" size
		VertexBuffer(std::initializer_list<BufferAttribute> attribs, uint32_t size);
		~VertexBuffer();

		void Bind();
		void Unbind();

		// Reallocates data for the buffer
		void Resize(uint32_t size);
		// This version of SetData sets the buffer's complete data
		void SetData(const void* data, uint32_t size);
		// This version of SetData sets a portion of the buffer's data
		// Needs to have some data allocated first via the second constructor or Resize
		void SetData(const void* data, uint32_t size, uint32_t offset);

		const std::vector<BufferAttribute>& GetIncludedAttributes() const { return m_included; }
		uint32_t GetStride() const { return m_stride; }
	private:
		GLuint m_id;
		uint32_t m_stride = 0;
		std::vector<BufferAttribute> m_included;
	};
}