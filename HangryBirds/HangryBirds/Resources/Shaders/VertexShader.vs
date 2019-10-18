#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 fragColor;
out vec2 fragTexCoord;

uniform float currentTime;
uniform mat4 MVP;

uniform float TexHeight;
uniform float TexWidth;
uniform float xOffset;
uniform float yOffset;

void main()
{
	gl_Position = MVP * vec4(position, 1.0);
	fragColor = color;
	fragTexCoord.x = (texCoord.x * TexWidth) + xOffset;
	fragTexCoord.y = (texCoord.y * TexHeight) + yOffset;
}