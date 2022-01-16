#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texIndex;
layout(location = 3) in vec4 color;

out vec2 v_TexCoord;
out vec4 v_Color;
out float v_TexIndex;

uniform mat4 u_MVP;

void main()
{
	v_Color = color;
	v_TexCoord = texCoord;
	v_TexIndex = texIndex;
	gl_Position = u_MVP * position;
};