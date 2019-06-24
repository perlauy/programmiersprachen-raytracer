#define _USE_MATH_DEFINES

#include "sphere.hpp"
#include <cmath>


Sphere::Sphere() :
  center_{0.f,0.f,0.f},
  radius_{1.f}
{}

Sphere::Sphere(glm::vec3 const& center, float radius) :
  center_{center},
  radius_{radius}
{}

float Sphere::area() const {
  return 4 * M_PI * std::pow(radius_,2);
}

float Sphere::volume() const {
  return 4 * M_PI * std::pow(radius_,3) / 3;
}