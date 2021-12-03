#include "SandboxLayer.h"

using namespace GLCore;
using namespace GLCore::Utils;

SandboxLayer::SandboxLayer()
{
}

SandboxLayer::~SandboxLayer()
{
}

void SandboxLayer::OnAttach()
{
	EnableGLDebugging();

	// For now gonna use this abstraction
	m_shader = Shader::FromGLSLTextFiles(
		"assets/test.vert.glsl",
		"assets/test.frag.glsl"
	);

	// Init here
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	m_buffer = new OpenGL::VertexBuffer({
		{ "pos", OpenGL::Datatype::Float2 },
		{ "uv",  OpenGL::Datatype::Float2 },
	});
	float data[] = {
		// Position      UVs         (Packed as specified in the layout)
		-.5f, -.5f,    0.0f, 0.0f,
		 .5f, -.5f,    1.0f, 0.0f,
		 .5f,  .5f,    1.0f, 1.0f,
		-.5f, -.5f,    0.0f, 0.0f,
		 .5f,  .5f,    1.0f, 1.0f,
		-.5f,  .5f,    0.0f, 1.0f,
	};
	m_buffer->SetData(data, sizeof(data));
	m_buffer->Bind();

	uint32_t index = 0;
	for (OpenGL::BufferAttribute attrib : m_buffer->GetIncludedAttributes()) {
		// Culmination of everything in the buffer class
		glVertexAttribPointer(
			index,
			OpenGL::GetElementCount(attrib.Type),
			OpenGL::GetBaseType(attrib.Type),
			GL_FALSE,
			m_buffer->GetStride(),
			(const void*) attrib.Offset);
		glEnableVertexAttribArray(index);
		index++;
	}
}

void SandboxLayer::OnDetach()
{
	// Shutdown here
	delete m_shader;
	glDeleteVertexArrays(1, &m_vao);
	delete m_buffer;
}

void SandboxLayer::OnEvent(Event& event)
{
	// Events here
}

void SandboxLayer::OnUpdate(Timestep ts)
{
	// Render here
	glUseProgram(m_shader->GetRendererID());
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6); // Count is hardcoded here for now
}

void SandboxLayer::OnImGuiRender()
{
	// ImGui here
}
