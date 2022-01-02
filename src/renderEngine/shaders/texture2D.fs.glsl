#version 330

in vec2 vTextCoor;

out vec3 fFragColor;

uniform sampler2D uTexture;

void main() {
  fFragColor = vec3(texture(uTexture,vTextCoor).xyz);
  //fFragColor = vec3(1.f,1.f,1.f);
};