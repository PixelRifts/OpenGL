#include "Buffer.h"

namespace OpenGL {
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
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}


	IndexBuffer::IndexBuffer()
	{
		glGenBuffers(1, &m_id);
	}

	IndexBuffer::IndexBuffer(uint32_t size)
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}
	
	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}

	void IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	
	void IndexBuffer::Resize(uint32_t size)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	void IndexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void IndexBuffer::SetData(const void* data, uint32_t size, uint32_t offset)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
	}
}