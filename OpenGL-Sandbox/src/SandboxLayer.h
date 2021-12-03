#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>
#include "OpenGL/Buffer.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/Shader.h"
#include "OpenGL/Texture.h"

class SandboxLayer : public GLCore::Layer
{
public:
	SandboxLayer();
	virtual ~SandboxLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(GLCore::Event& event) override;
	virtual void OnUpdate(GLCore::Timestep ts) override;
	virtual void OnImGuiRender() override;

private:
	float m_time;
	OpenGL::VertexArray* m_vao;
	OpenGL::VertexBuffer* m_buffer;
	OpenGL::IndexBuffer* m_indexbuffer;
	OpenGL::Shader* m_shader;
	OpenGL::Texture2D* m_texture;
};