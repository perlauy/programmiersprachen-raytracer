#include "box.hpp"


Box::Box() :
  Shape(),
  minimum_{0.f,0.f,0.f},
  maximum_{1.f,1.f,1.f}
{}

Box::Box(std::string const& name, std::shared_ptr<Material> const& material, glm::vec3 const& minimum, glm::vec3 const& maximum) : 
  Shape(name, material),
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

HitPoint Box::intersect(Ray const& ray, float& t) const {
  glm::vec3 central = minimum_ + (1.0f/2.0f) * (maximum_ - minimum_); 
  glm::vec3 origin_to_central = central - ray.origin;
  HitPoint result{};
  for (int index = 0; index < 3; ++index) {
    if (origin_to_central[index] != 0) {
      if (origin_to_central[index] < 0) {
        if (hit_test(result, ray, maximum_[index], 0)) {
          t = result.t;
          return result;
        }
      } else {
        if (hit_test(result, ray, minimum_[index], 0)) {
          t = result.t;
          return result;
        }
      }
    }
  }
  t = result.t;
  return result;
}

bool Box::hit_test(HitPoint& result, Ray const& ray, float fixed_value, int index) const {
  glm::vec3 normalized_direction = glm::normalize(ray.direction);
  float distance = (fixed_value - ray.origin[index])/normalized_direction[index];
  glm::vec3 resulting_point = ray.origin + normalized_direction * distance;
  if (distance >= 0 and (minimum_[(index + 1) % 3] <= resulting_point[(index + 1) % 3] <= maximum_[(index + 1) % 3]) &&
    (minimum_[(index + 2) % 3] <= resulting_point[(index + 2) % 3] <= maximum_[(index + 2) % 3])) {
    result = HitPoint{
      true,
      distance,
      name_,
      material_,
      resulting_point,
      ray.direction
    };
    return true;
  } else {
    return false;
  }
}

std::ostream& Box::print(std::ostream& os) const {
  Shape::print(os);
  os << "Type: Box\n";
  os << "Minimum: (" << minimum_[0] << ", " << minimum_[1] << ", " << minimum_[2] << ")\tMaximum: (" << maximum_[0] << ", " << maximum_[1] << ", " << maximum_[2] << ")\n";
  return os;
}