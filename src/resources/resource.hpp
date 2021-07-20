#pragma once
#include <iostream>
#include <string>

struct Resource {
  virtual ~Resource() = default;
  virtual void print() const = 0;
};

struct File : Resource {
  std::string_view filename;
  virtual void print() const override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  };
};