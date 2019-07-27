#ifndef LIGHT_HPP
#define LIGHT_HPP

// Standard libraries
#include <string>


struct Light {
  // TO BE IMPLEMENTED

  friend bool operator<(Light const& lhs, Light const& rhs) {
    return lhs.name < rhs.name;
  };

  std::string name = "";
  glm::vec3 pos{};
  Color color{};
  float brightness = 0;

};

#endif //#define LIGHT_HPP
