#version 330

in vec3 vPosition_vs; 
in vec3 vNormal_vs; 
in vec2 vTexCoords;
in vec3 vWorldPosition;

out vec3 fFragColor;

//Textures
uniform sampler2D uTextureDiffuse;
uniform sampler2D uTextureSpecular;
uniform float uShininess;
uniform mat4 uMVMatrix;


//Lumière directionnelle
const vec3 LightDirection = normalize(vec3(0.1, 0.8, 0.2));
const vec3 LightColor= vec3(0.2, 0.1, 1.)*1.4;

//Lumiere ponctuelle
const vec3 LightPosition = vec3(0., 1., 5.);
const vec3 LightPonctualColor= vec3(1., 0.97, 0.4)*20;

vec3 Light(vec3 direction, vec3 color){
    vec3 diffuse=clamp(dot(vNormal_vs, direction),0, 1)* texture(uTextureDiffuse, vTexCoords).rgb;
    vec3 halfVector=(direction+normalize(-vPosition_vs))/2;
    vec3 specular=texture(uTextureSpecular, vTexCoords).rgb*pow(clamp(dot(halfVector,vNormal_vs),0,1),uShininess);
    return color* (diffuse + specular);
}


void main() {
    vec3 LightPos= LightPosition *
    float dist= distance(vPosition_vs, LightPosition);
    //fFragColor= Light(LightDirection,LightColor);+ Light(normalize(LightPosition - vWorldPosition), LightPonctualColor/(dist*dist));
    fFragColor=Light(normalize(LightPosition - vWorldPosition), LightPonctualColor/(dist*dist));
}