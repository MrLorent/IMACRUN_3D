#version 330

in vec3 vPosition_vs; 
in vec3 vNormal_vs; 
in vec2 vTexCoords;

out vec3 fFragColor;

uniform sampler2D uTextures[];
uniform int uTextures_size;


void main() {
    fFragColor= texture(uTextures[0],vTexCoords).xyz;
}