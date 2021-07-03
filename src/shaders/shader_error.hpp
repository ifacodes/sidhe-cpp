#pragma once

#include <stdexcept>

namespace sidhe {

class shader_error : virtual public std::runtime_error {
 public:
  explicit shader_error(const std::string &msg) : std::runtime_error(msg) {}

  virtual ~shader_error() throw() {}

 protected:
  std::string_view msg;
};

}  // namespace sidhe