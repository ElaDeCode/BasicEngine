#version 450 core

layout (location = 0) vec3 aPos;
out vec2 TexCoords;

void main() {
  gl_Position = vec4(aPos, 1);
  TexCoords = aPos;
}