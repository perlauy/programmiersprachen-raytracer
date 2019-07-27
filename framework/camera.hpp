#ifndef CAMERA_HPP
#define CAMERA_HPP

// External libraries
#include <glm/vec3.hpp>

// Standard libraries
#include <string>


struct Camera {
  
  friend bool operator<(Camera const& lhs, Camera const& rhs) {
    return lhs.name < rhs.name;
  };

  std::string name = "";
  float angle = 60.0; // 0 to 180
  glm::vec3 position = {0.0f, 0.0f, 0.0f};
  glm::vec3 direction = {0.0f, 0.0f, -1.0f};
  glm::vec3 up = {0.0f, 1.0f, 0.0f};

};

#endif //#define CAMERA_HPP
