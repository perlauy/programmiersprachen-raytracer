#ifndef HIT_POINT_HPP
#define HIT_POINT_HPP

#include "material.hpp"
#include <cmath>
#include <string>
#include <glm/vec3.hpp>
#include <memory>

struct HitPoint {

  friend std::ostream& operator<<(std::ostream& os, HitPoint const& hp)
    {
      if (hp.hit) {
        os << "HitPoint: " << hp.object << std::endl;
        os << "Distance: " << hp.t << "\t Point: (" << hp.point[0] << ", " << hp.point[1] << ", " << hp.point[2] <<")\n" << std::endl;
      } else {
        os << "HitPoint missed\n" << hp.t << std::endl;
      }
      return os;
    }

  bool hit = false;
  float t = HUGE_VALF;
  std::string object = "";
  std::shared_ptr<Material> material_ = nullptr;
  glm::vec3 point{};
  glm::vec3 direction{};
};

#endif
