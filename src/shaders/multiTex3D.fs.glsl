#version 300 es

precision mediump float;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoords;

out vec3 fFragColor;

uniform sampler2D uEarthTexture;
uniform sampler2D uCloudTexture;

void main() {
    fFragColor = texture(uEarthTexture, vTexCoords).xyz + texture(uCloudTexture, vTexCoords).xyz;
};