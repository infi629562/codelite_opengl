#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;


// texture samplers
uniform sampler2D texture0;
uniform sampler2D texture1;
void main()
{
    // FragColor = vec4(ourColor, 1.0f);
	// FragColor = texture(ourTexture, TexCoord);
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = mix(texture(texture0, TexCoord), texture(texture1, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.5) * vec4(ourColor, 1.0f);
}
