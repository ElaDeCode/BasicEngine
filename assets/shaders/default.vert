#version 450 core

layout(location = 0) in vec3 aPos;

out vec3 fragPos;

uniform vec3 uPos = vec3(0);
uniform vec3 uCameraPosition = vec3(0);
uniform mat3 uCameraRotation = mat3(1, 0, 0, //
                               0, 1, 0, //
                               0, 0, 1);

float wRatio = 0.75;
float perspectiveZ = 0.7;

void main() {
  vec3 relativePos = (aPos - uCameraPosition) * uCameraRotation;
  vec4 view = vec4(relativePos.xy, relativePos.z / 100.0, 1 + perspectiveZ * relativePos.z);
  vec4 renderPos = vec4(view.x * wRatio, view.yzw);
  gl_Position = renderPos;
  fragPos = aPos + vec3(0.5);
}