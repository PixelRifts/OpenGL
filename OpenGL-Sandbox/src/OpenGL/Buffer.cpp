#include "Buffer.h"

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

	BufferAttribute::BufferAttribute(std::string name, Datatype type)
		: Name(name), Type(type), Offset(0)
	{
	}
	
	VertexBuffer::VertexBuffer(std::initializer_list<BufferAttribute> attribs)
	{
		glGenBuffers(1, &m_id);
		m_included = attribs;

		// Calculates offset and stride based on described attributes
		size_t offset = 0;
		m_stride = 0;
		for (auto& element : m_included)
		{
			element.Offset = offset;
			offset += GetSize(element.Type);
			m_stride += GetSize(element.Type);
		}
	}
	
	VertexBuffer::VertexBuffer(std::initializer_list<BufferAttribute> attribs, uint32_t size)
	{
		glGenBuffers(1, &m_id);
		m_included = attribs;

		// Calculates offset and stride based on described attributes
		size_t offset = 0;
		m_stride = 0;
		for (auto& element : m_included)
		{
			element.Offset = offset;
			offset += GetSize(element.Type);
			m_stride += GetSize(element.Type);
		}

		if (size % m_stride != 0) {
			// Safety check. you normally want full vertices in buffers. so if a full vertex cannot fit, Warn
			LOG_WARN("Buffer's size is weird\n");
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::Resize(uint32_t size)
	{
		if (size % m_stride != 0) {
			// Safety check. you normally want full vertices in buffers. so if a full vertex cannot fit, Warn
			LOG_WARN("Buffer's size is weird\n");
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	void VertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void VertexBuffer::SetData(const void* data, uint32_t size, uint32_t offset)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}
}