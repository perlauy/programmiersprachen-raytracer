#include "box.hpp"


Box::Box() :
  Shape(),
  minimum_{0.f,0.f,0.f},
  maximum_{1.f,1.f,1.f}
{}

Box::Box(std::string const& name, Color const& color, glm::vec3 const& minimum, glm::vec3 const& maximum) : 
  Shape(name, color),
  minimum_{minimum},
  maximum_{maximum}
{}


float Box::area() const {
  return (
    (maximum_[0] - minimum_[0]) * (maximum_[1] - minimum_[1])
    + (maximum_[0] - minimum_[0]) * (maximum_[2] - minimum_[2])
    + (maximum_[1] - minimum_[1]) * (maximum_[2] - minimum_[2])
    ) * 2;
}

float Box::volume() const {
  return (maximum_[0] - minimum_[0]) * (maximum_[1] - minimum_[1]) * (maximum_[2] - minimum_[2]);
}

HitPoint Box::intersect(Ray const& ray) const {
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
    point, // selbst berechnen (don't call twice)
    ray.direction
  };
}

std::ostream& Box::print(std::ostream& os) const {
  Shape::print(os);
  os << "Type: Box\n";
  os << "Minimum: (" << minimum_[0] << ", " << minimum_[1] << ", " << minimum_[2] << ")\tMaximum: (" << maximum_[0] << ", " << maximum_[1] << ", " << maximum_[2] << ")\n";
  return os;
}