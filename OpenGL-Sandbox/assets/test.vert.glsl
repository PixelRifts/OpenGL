#version 450 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_UV;

out vec2 v_UV;

void main()
{
	gl_Position = vec4(a_Position, 0.0, 1.0f);
	v_UV = a_UV;
}