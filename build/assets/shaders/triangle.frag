#version 450 core
out vec4 FragColor;
  
in vec2 TexCoord;
uniform sampler2D ourTexture;

uniform int u_frameNumber;
uniform float u_frameWidth;

void main()
{
    FragColor = texture(ourTexture, TexCoord + vec2(u_frameWidth * u_frameNumber, 0));
}