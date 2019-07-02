#ifndef HIT_POINT_HPP
#define HIT_POINT_HPP

#include "color.hpp"

#include <string>
#include <glm/vec3.hpp>

struct HitPoint {
  bool hit = false;
  float t = 0.0f;
  std::string object = '';
  Color color{};
  glm::vec3 point{};
  glm::vec3 direction{};
};

#endif
