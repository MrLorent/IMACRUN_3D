

#include <string>
#include <vector>
#include "./glm.hpp"


// -------- à metre dans menu.hpp -----------


/* lit texture et un couple de shaders : 
pour générer une texture de texte utiliser CBFG puis importer dans PAINT  */
void initText2D(const std::string texturePath);

/* Générer rectangle avec positions appropriées*/
void printText2D(const char * text, int x, int y, int size);
void cleanupText2D();




// on doit remplir ça
std::vector<glm::vec2> vertices;
std::vector<glm::vec2> UVs;

void printText2D(std::string text, int x, int y, int size);
{
    
    for( size_t i =0; i<text.size() ; i++){
        
        glm::vec2 vertex_up_left = glm::vec2(x+i*size, y+size);
        glm::vec2 vertex_up_right = glm::vec2(x+i*size + size, y+size);
        glm::vec2 vertex_up_left = glm::vec2(x+i*size + size, y);
        glm::vec2 vertex_up_left = glm::vec2(x+i*size + size, y);

        vertices.push_back(vertex_up_left);
        vertices.push_back(vertex_down_left);
        vertices.push_back(vertex_up_right);

        vertices.push_back(vertex_down_right);
        vertices.push_back(vertex_up_right);
        vertices.push_back(vertex_down_left;


        char character = text[i];
        float uv_x = (character%16)/16.0f;
        float uv_y = (character/16)/16.0f;

        glm::vec2 uv_up_left = glm::vec2(uv_x, 1.0f-uv_y);
        glm::vec2 uv_up_left = glm::vec2(uv_x, 1.0f-uv_y);
    

    }

}
