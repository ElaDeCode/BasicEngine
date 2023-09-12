#version 450 core

layout(location = 0) in vec3 aPos;

out vec3 fragPos;
out vec3 vertPos;

uniform float time = 0.0001;
uniform mat4 projection;
uniform mat4 model;

flat out int InstanceID;

vec3 rotate(vec3 pos, int InstanceID);

vec3 instanceOffset;

void main() {
  InstanceID = gl_InstanceID;
  instanceOffset =
      vec3((InstanceID % 50), ((InstanceID / 50) % 50), (InstanceID / 2500));
  vec3 pos = rotate(aPos + instanceOffset * 1, InstanceID);
  gl_Position = projection * vec4(pos, 1);
  fragPos = aPos + vec3(0.5);
  vertPos = pos;
}

vec3 timeOffset = time + vec3(20);
vec3 fakeTime = vec3(timeOffset.x, timeOffset.y, timeOffset.z * 0.01);
vec3 rotate(vec3 pos, int InstanceID) {
  float yaw = instanceOffset.x * fakeTime.x * 0.1;
  float pitch = instanceOffset.y * fakeTime.y * 0.1;
  float roll = instanceOffset.z * fakeTime.z * -0.1;

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