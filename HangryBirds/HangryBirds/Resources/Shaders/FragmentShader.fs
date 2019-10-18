#version 450 core

in vec3 fragColor;
in vec2 fragTexCoord;

out vec4 color;

uniform float currentTime;

uniform sampler2D tex;


void main(void)
{
	vec4 texColor = texture(tex, fragTexCoord);
	if (texColor.a < 0.1)
	{
		discard;
	}
	color = texColor;
}