#version 330

in vec2 vTextCoor;

uniform sampler2D uTexture;

out vec3 fFragColor;

void main() {
  fFragColor = vec3(texture(uTexture,vTextCoor).xyz);
};