#version 300 es

mat3 rotate(float a);

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aTexturePosition;

out vec2 vTextCoor;

void main() {
  vTextCoor = aTexturePosition;
  gl_Position = vec4(aVertexPosition, 1);
};