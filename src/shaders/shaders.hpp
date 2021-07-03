#pragma once

#include <gl/glew.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "shader_error.hpp"

class Shader {
 public:
  unsigned int ID;
  Shader(std::string path, bool vertex_b, bool fragment_b) {
    std::string shader_source;
    std::ifstream file;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
      file.open(path);
      std::stringstream ss;
      ss << file.rdbuf();
      file.close();
      shader_source = ss.str();
    } catch (std::ifstream::failure& e) {
      std::cout << "Couldn't load shader." << std::endl;
    }

    unsigned int vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    const char* source[2] = {"#version 420 core\n#define VERTEX\n",
                             shader_source.c_str()};
    glShaderSource(vertex, 2, source, NULL);

    try {
      int success;
      glCompileShader(vertex);
      glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
      if (!success) {
        char log[512];
        glGetShaderInfoLog(vertex, 512, NULL, log);
        throw sidhe::shader_error(log);
      }

    } catch (sidhe::shader_error& e) {
      std::cout << e.what() << std::endl;
    }

    const char* fsource[2] = {"#version 420 core\n#define FRAGMENT\n",
                              shader_source.c_str()};
    glShaderSource(fragment, 2, fsource, NULL);

    try {
      int success;
      glCompileShader(fragment);
      glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
      if (!success) {
        char log[512];
        glGetShaderInfoLog(fragment, 512, NULL, log);
        throw sidhe::shader_error(log);
      }

    } catch (sidhe::shader_error& e) {
      std::cout << e.what() << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // error checking!

    glDeleteShader(vertex);
    glDeleteShader(fragment);
  }

  void use() { glUseProgram(ID); }
};