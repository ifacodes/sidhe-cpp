#pragma once

#include <GL/glew.h>

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

// TODO: move this somewhere eventually
struct Vertex {
  float x;
  float y;
};

class Map {
 public:
  Map() : width(15), height(10) {
    vertices.resize((width + 1) * (height + 1));
    indices.resize((width * 6) * height);
    // generate vertices based on amount of tiles
    for (int i = 0; i < height + 1; i++) {
      for (int j = 0; j < width + 1; j++) {
        vertices[i * (width + 1) + j] = {
            // static_cast<float>((((j - 0) * (1.0 + 1.0)) / (width + 2))
            // - 1.0),
            static_cast<float>(((j * 2.0) / (width)) - 1.0),
            static_cast<float>(((i * 2.0) / (height)) - 1.0)};
      }
    }

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        indices[(6 * (j + (width * i)))] = j + (i * (width + 1));
        indices[(6 * (j + (width * i))) + 1] =
            j + (i * (width + 1)) + width + 1;
        indices[(6 * (j + (width * i))) + 2] =
            j + (i * (width + 1)) + width + 2;
        indices[(6 * (j + (width * i))) + 3] = j + (i * (width + 1));
        indices[(6 * (j + (width * i))) + 4] = j + (i * (width + 1)) + 1;
        indices[(6 * (j + (width * i))) + 5] =
            j + (i * (width + 1)) + width + 2;
      }
    }

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 &vertices.front(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
                 &indices.front(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
  }
  ~Map() {}

  void render() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  }  // render the map

 private:
  unsigned int VBO;
  unsigned int EBO;
  unsigned int VAO;
  uint8_t width, height;
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;
  std::vector<uint8_t> map_data;
};
