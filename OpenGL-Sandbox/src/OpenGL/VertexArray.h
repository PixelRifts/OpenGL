#pragma once

#include "Buffer.h"

namespace OpenGL {
	// This is a collection of buffers or rather attributes andd associates each attribute with an index.
	// This is what can be drawn using a draw call
	class VertexArray {
	public:
		VertexArray();
		~VertexArray();

		void Bind();
		void Unbind();

		// Add A Buffer to this vertex array with the starting index 0.
		inline void AddBuffer(VertexBuffer* buffer) { AddBuffer(buffer, 0); };
		// Add A Buffer to this vertex array with the starting index start_index.
		void AddBuffer(VertexBuffer* buffer, int start_index);

		void SetIndexBuffer(IndexBuffer* buffer);

	private:
		GLuint m_id;
		std::vector<VertexBuffer*> m_buffers;
		IndexBuffer* m_index_buffer;
	};
}