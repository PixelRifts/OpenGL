#include "SandboxLayer.h"

#include <GLCore.h>
#include <GLCoreUtils.h>

SandboxLayer::SandboxLayer()
{
	m_time = 0;
}

SandboxLayer::~SandboxLayer()
{
}

void SandboxLayer::OnAttach()
{
	GLCore::Utils::EnableGLDebugging();

	// For now gonna use this abstraction
	m_shader = new OpenGL::Shader(
		"assets/test.vert.glsl",
		"assets/test.frag.glsl"
	);

	m_texture = new OpenGL::Texture2D("assets/Smiley.png");

	// Init here
	m_vao = new OpenGL::VertexArray();
	m_vao->Bind();

	m_buffer = new OpenGL::VertexBuffer({
		{ "pos", OpenGL::Datatype::Float2 },
		{ "uv",  OpenGL::Datatype::Float2 },
	});
	float data[] = {
		// Position      UVs         (Packed as specified in the layout)
		-.5f, -.5f,    0.0f, 0.0f,
		 .5f, -.5f,    1.0f, 0.0f,
		 .5f,  .5f,    1.0f, 1.0f,
		-.5f,  .5f,    0.0f, 1.0f,
	};
	m_buffer->SetData(data, sizeof(data));
	m_buffer->Bind();

	m_vao->AddBuffer(m_buffer);

	m_indexbuffer = new OpenGL::IndexBuffer();
	m_indexbuffer->Bind();
	// Indices index into the vertices in the vao
	int indices[] = {
		0, 1, 2, 0, 2, 3
	};
	m_indexbuffer->SetData(indices, sizeof(indices));

	m_vao->SetIndexBuffer(m_indexbuffer);
}

void SandboxLayer::OnDetach()
{
	// Shutdown here
	delete m_indexbuffer;
	delete m_buffer;
	delete m_vao;
	delete m_shader;
	delete m_texture;
}

void SandboxLayer::OnEvent(GLCore::Event& event)
{
	// Events here
}

void SandboxLayer::OnUpdate(GLCore::Timestep ts)
{
	m_time += ts.GetSeconds();

	// Render here
	m_shader->Bind();
	m_texture->Bind(0);
	m_shader->SetInt("u_Texture", 0);
	m_shader->SetVector4("u_Color", glm::vec4(glm::sin(m_time), glm::cos(m_time), glm::sin(2 * m_time), 1.f));
	m_vao->Bind();

	// Count is hardcoded here for now
	// Indices are nullptr since they are associated with the vao
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void SandboxLayer::OnImGuiRender()
{
	// ImGui here
}
