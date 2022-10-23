#include "Grid.h"
#include <vector>
#include <iostream>
#include <GLM/ext.hpp>



using namespace std;

Grid::Grid(VAO* _vao)
{
    slices = SLICES;
    length = 0; //initialize
    vao = _vao;
}

void Grid::init()
{
    vector<glm::vec3> vertices;
    vector<glm::uvec4> indices;

    for (int j = 0; j <= slices; ++j) {
        for (int i = 0; i <= slices; ++i) {
            float x = (float)i / (float)slices;
            float y = 0;
            float z = (float)j / (float)slices;
            vertices.push_back(glm::vec3(x, y, z));
        }
    }

    for (int j = 0; j < slices; ++j) {
        for (int i = 0; i < slices; ++i) {

            int row1 = j * (slices + 1);
            int row2 = (j + 1) * (slices + 1);

            indices.push_back(glm::uvec4(row1 + i, row1 + i + 1, row1 + i + 1, row2 + i + 1));
            indices.push_back(glm::uvec4(row2 + i + 1, row2 + i, row2 + i, row1 + i));

        }
    }
    //init and bind VAO
    vao->bindVAO();
    vbo = new VBO(glm::value_ptr(vertices[0]), vertices.size() * sizeof(glm::vec3));
    ibo = new IBO(glm::value_ptr(indices[0]), indices.size() * sizeof(glm::uvec4));
    vao->linkVBO(*vbo, 0);
    vao->unbindVAO();

    length = (GLuint)indices.size() * 4;
    isInited = true;
}

void Grid::cleanup()
{
    if (!isInited) {
        return;
    }

    if (m_vboVertex) {
        glDeleteBuffers(1, &m_vboVertex);
    }
    if (m_vboIndex) {
        glDeleteBuffers(1, &m_vboIndex);
    }
    if (m_vao) {
        glDeleteVertexArrays(1, &m_vao);
    }

    isInited = false;
    m_vao = 0;
    m_vboVertex = 0;
    m_vboIndex = 0;
}

void Grid::draw()
{
    if (!isInited) {
        std::cout << "please call init() before draw()" << std::endl;
    }
    glEnable(GL_DEPTH_TEST);
    vao->bindVAO();
    vbo->bindVBO();
    glDrawElements(GL_LINES, length, GL_UNSIGNED_INT, NULL);
    vao->unbindVAO();
    vbo->unbindVBO();
    glDisable(GL_DEPTH_TEST);
}
