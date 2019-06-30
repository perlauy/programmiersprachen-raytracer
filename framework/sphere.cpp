#define _USE_MATH_DEFINES

#include "sphere.hpp"
#include "color.hpp"
#include "hit_point.hpp"
#include "ray.hpp"
#include <cmath>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

Sphere::Sphere() :
  Shape(),
  center_{0.f,0.f,0.f},
  radius_{1.f}
{}

Sphere::Sphere(std::string name, Color color, glm::vec3 const& center, float radius) : 
  Shape(name, color),
  center_{center},
  radius_{radius}
{}

float Sphere::area() const {
  return 4 * M_PI * std::pow(radius_,2);
}

float Sphere::volume() const {
  return 4 * M_PI * std::pow(radius_,3) / 3;
}

std::ostream& Sphere::print(std::ostream& os) const {
  Shape::print(os);
  os << "Type: Sphere\n";
  os << "Center: (" << center_[0] << ", " << center_[1] << ", " << center_[2] << ")" << "\tRadius: " << radius_ << "\n";
  return os;
}

HitPoint Sphere::intersect(Ray ray) const {

  glm::vec3 normalized_direction = glm::normalize(ray.direction);
  float distance = 0.0f;

  bool is_intersected_distance = glm::intersectRaySphere(
    ray.origin,
    normalized_direction,
    center_,
    radius_ * radius_,
    distance
  );
  
  glm::vec3 point{};
  glm::vec3 normal{};
  bool is_intersected_point = glm::intersectRaySphere(
    ray.origin,
    normalized_direction,
    center_,
    radius_,
    point,
    normal
  );

  return HitPoint{
    is_intersected_distance,
    distance,
    name_,
    color_,
    point,
    ray.direction
  };
}


