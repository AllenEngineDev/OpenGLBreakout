#shader vertex
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoords;

out vec3 o_Color;
out vec2 o_TexCoords;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position.xyz, 1.0f);
	o_Color = color;
	o_TexCoords = texCoords;
}

#shader fragment
#version 330 core
out vec4 color;

in vec3 o_Color;
in vec2 o_TexCoords;

uniform sampler2D ourTexture2;
uniform sampler2D ourTexture;

void main()
{
	color = mix(texture(ourTexture, o_TexCoords), texture(ourTexture2, o_TexCoords) , 0.2);
}