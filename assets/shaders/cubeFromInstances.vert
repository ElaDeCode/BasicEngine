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

  vec3 rotated = rotate(aPos, InstanceID);
  vec3 relativePos = (rotated - uCameraPosition + //
                      vec3(1.4, 0, 0) * (InstanceID % 50) +
                      vec3(0, 0, 1.4) * ((InstanceID / 50) % 50) +
                      vec3(0, 1.4, 0) * (InstanceID / 2500)) *
                     uCameraRotation;

  vec4 view = vec4(relativePos.xy, relativePos.z / 100.0,
                   1 + perspectiveZ * relativePos.z);
  vec4 renderPos = vec4(view.x * wRatio, view.yzw);
  gl_Position = renderPos;
  fragPos = aPos + vec3(0.5);
}

vec3 rotate(vec3 pos, int InstanceID) {
  float yaw = (InstanceID % 50) * uTime;
  float pitch = ((InstanceID / 50) % 50) * uTime;
  float roll = (InstanceID / 2500) * uTime;

  float sinYaw = sin(radians(yaw));
  float cosYaw = cos(radians(yaw));
  float sinPitch = sin(radians(pitch));
  float cosPitch = cos(radians(pitch));
  float sinRoll = sin(radians(roll));
  float cosRoll = cos(radians(roll));

  mat3 yawRotation = mat3(cosYaw, 0, sinYaw, 0, 1, 0, -sinYaw, 0, cosYaw);
  mat3 pitchRotation =
      mat3(1, 0, 0, 0, cosPitch, -sinPitch, 0, sinPitch, cosPitch);
  mat3 rollRotation = mat3(cosRoll, -sinRoll, 0, sinRoll, cosRoll, 0, 0, 0, 1);

  vec3 rotated = yawRotation * pitchRotation * rollRotation * pos;

  return rotated;
}