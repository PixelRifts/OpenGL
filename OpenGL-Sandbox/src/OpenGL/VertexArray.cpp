#include "VertexArray.h"

namespace OpenGL {
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_id);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::AddBuffer(VertexBuffer* buffer, int start_index)
	{
		glBindVertexArray(m_id);
		m_buffers.push_back(buffer);
		uint32_t index = start_index;
		for (BufferAttribute attrib : buffer->GetIncludedAttributes()) {
			// Culmination of everything in the buffer class
			glVertexAttribPointer(
				index,
				GetElementCount(attrib.Type),
				GetBaseType(attrib.Type),
				GL_FALSE,
				buffer->GetStride(),
				(const void*)attrib.Offset);
			glEnableVertexAttribArray(index);
			index++;
		}
	}
	
	void VertexArray::SetIndexBuffer(IndexBuffer* buffer)
	{
		m_index_buffer = buffer;
		// Binding an Index Buffer while a vao is bound connects them
		glBindVertexArray(m_id);
		buffer->Bind();
	}
}