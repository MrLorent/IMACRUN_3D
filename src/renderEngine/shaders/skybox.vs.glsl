#version 330

// Attributs de sommet
layout(location = 0) in vec3 aVertexPosition; // Position du sommet
layout(location = 2) in vec2 aVertexTexCoords; // Coordonnées de texture du sommet

// Matrices de transformations reçues en uniform
uniform mat4 uMVPMatrix;


// Sorties du shader
out vec2 vTexCoords; // Coordonnées de texture du sommet

void main() {
    // Passage en coordonnées homogènes
    vec4 vertexPosition = vec4(aVertexPosition, 1);

    // Calcul des valeurs de sortie
    vTexCoords = aVertexTexCoords;


    // Calcul de la position projetée
    gl_Position = uMVPMatrix * vertexPosition;
}