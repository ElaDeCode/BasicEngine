#version 450 core

layout(location = 0) in vec3 aPos;

out vec3 fragPos;

uniform float uTime = 0.0001;
uniform ivec2 uResolution;
uniform vec3 uPos = vec3(0);
uniform vec3 uCameraPosition = vec3(0);
uniform mat3 uCameraRotation = mat3(1, 0, 0, //
                                    0, 1, 0, //
                                    0, 0, 1);

flat out int InstanceID;

float wRatio = float(uResolution.y) / float(uResolution.x);
float perspectiveZ = 0.7;

vec3 rotate(vec3 pos, int InstanceID);

void main() {
  InstanceID = gl_InstanceID;

  vec3 relativePos = (aPos - uCameraPosition) * uCameraRotation;

  vec4 view = vec4(relativePos.xy, relativePos.z / 100.0,
                   1 + perspectiveZ * relativePos.z);
  vec4 renderPos = vec4(view.x * wRatio, view.yzw);
  gl_Position = renderPos;
  fragPos = aPos + vec3(0.5);
}