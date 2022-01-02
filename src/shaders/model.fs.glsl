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

uniform vec3 uLightPos1;
uniform vec3 uLightPos2;

//Lumière directionnelle
const vec3 LightDirection = normalize(vec3(0.8, 0.8, 0.2));
const vec3 LightColor= vec3(98.f/255, 85.f/255, 128.f/255);

//Lumiere ponctuelle
const vec3 LightPosition = vec3(0., 1., 5.);
const vec3 LightPonctualColor= vec3(0.8, 0.2, 0.)*5;

vec3 Light(vec3 direction, vec3 color){
    vec3 diffuse=clamp(dot(vNormal_vs, direction),0, 1)* texture(uTextureDiffuse, vTexCoords).rgb;
    vec3 halfVector=(direction+normalize(-vPosition_vs))/2;
    vec3 specular=texture(uTextureSpecular, vTexCoords).rgb*pow(clamp(dot(halfVector,vNormal_vs),0,1),uShininess);
    return color* (diffuse + specular);
}


void main() {
    fFragColor = Light(LightDirection, LightColor);
    float dist = distance(vPosition_vs, uLightPos1);
    fFragColor += Light(normalize(uLightPos1 - vPosition_vs), LightPonctualColor/(dist*dist));
    dist = distance(vPosition_vs, uLightPos2);
    fFragColor += Light(normalize(uLightPos2 - vPosition_vs), LightPonctualColor/(dist*dist));
}