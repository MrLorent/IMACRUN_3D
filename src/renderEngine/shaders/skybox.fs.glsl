#version 330

in vec2 vTexCoords;

out vec3 fFragColor;

//Textures
uniform sampler2D uTextureDiffuse;


void main() {
    fFragColor= vec3(texture(uTextureDiffuse,vTexCoords).xyz);
}