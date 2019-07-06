#ifndef HIT_POINT_HPP
#define HIT_POINT_HPP

#include "material.hpp"

#include <string>
#include <glm/vec3.hpp>

struct HitPoint {
  bool hit = false;
  float t = 0.0f;
  std::string object = "";
  std::shared_ptr<Material> material_ = std::make_shared<Material>();
  glm::vec3 point{};
  glm::vec3 direction{};
};

#endif
