#version 450 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_UV;

// uniform mat4 u_ViewProjection;

void main()
{
	gl_Position = vec4(a_Position, 0.0, 1.0f);
}