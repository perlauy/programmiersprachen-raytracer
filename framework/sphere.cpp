#define _USE_MATH_DEFINES

#include "sphere.hpp"
#include "color.hpp"
#include "hit_point.hpp"
#include "ray.hpp"

#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

Sphere::Sphere() :
  Shape(),
  center_{0.f,0.f,0.f},
  radius_{1.f}
{ std::cout << "Constructor SPHERE" << std::endl; }

Sphere::Sphere(std::string const& name, std::shared_ptr<Material> const& material, glm::vec3 const& center, float radius) : 
  Shape(name, material),
  center_{center},
  radius_{radius}
{ std::cout << "Constructor SPHERE" << std::endl; }

Sphere::~Sphere() { std::cout << "Destructor SPHERE" << std::endl; }


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

HitPoint Sphere::intersect(Ray const& ray) const {

  glm::vec3 normalized_direction = glm::normalize(ray.direction);
  float distance = 0.0f;

  bool is_intersected_distance = glm::intersectRaySphere(
    ray.origin,
    normalized_direction,
    center_,
    radius_ * radius_,
    distance
  );
  
  glm::vec3 point = ray.origin + distance * normalized_direction;

  return HitPoint{
    is_intersected_distance,
    distance,
    name_,
    material_,
    point, // selbst berechnen (don't call twice)
    ray.direction
  };
}


