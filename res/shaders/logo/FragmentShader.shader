#version 410 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_Color;
in float v_TexIndex;

uniform sampler2D u_Textures[2];

void main()
{
	int texIndex = int(v_TexIndex);
	color = texture(u_Textures[texIndex], v_TexCoord) * v_Color;
};