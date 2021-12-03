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
	m_vao = new OpenGL::VertexArray();

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

	m_vao->AddBuffer(m_buffer);
}

void SandboxLayer::OnDetach()
{
	// Shutdown here
	delete m_buffer;
	delete m_vao;
	delete m_shader;
}

void SandboxLayer::OnEvent(Event& event)
{
	// Events here
}

void SandboxLayer::OnUpdate(Timestep ts)
{
	// Render here
	glUseProgram(m_shader->GetRendererID());
	m_vao->Bind();
	glDrawArrays(GL_TRIANGLES, 0, 6); // Count is hardcoded here for now
}

void SandboxLayer::OnImGuiRender()
{
	// ImGui here
}
