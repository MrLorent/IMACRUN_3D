#version 300 es

layout(location = 2) in vec2 aTexturePosition;

out vec2 vTextCoor;

void main() {
  vTextCoor = aTexturePosition;
  gl_Position = vec4(aVertexPosition, 1);
};