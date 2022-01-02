#version 330

in vec3 vPosition_vs; 
in vec3 vNormal_vs; 
in vec2 vTexCoords;

out vec3 fFragColor;

//Textures
uniform sampler2D uTextureDiffuse;
uniform sampler2D uTextureSpecular;
uniform float uShininess;
uniform mat4 uMVMatrix;

uniform vec3 uLightPos1; // In MVMatrix
uniform vec3 uLightPos2;
uniform vec3 uLightPos3; 
uniform vec3 uLightPos4;


void main() {
    fFragColor= vec3(texture(uTextureDiffuse,vTexCoords).xyz);
}