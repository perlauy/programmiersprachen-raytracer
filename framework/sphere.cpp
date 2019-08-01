#define _USE_MATH_DEFINES

#include "sphere.hpp"


Sphere::Sphere() :
  Shape(),
  center_{0.f,0.f,0.f},
  radius_{1.f}
{}

Sphere::Sphere(std::string const& name, std::shared_ptr<Material> const& material, glm::vec3 const& center, float radius) : 
  Shape(name, material),
  center_{center},
  radius_{radius}
{}

Sphere::~Sphere() {}


float Sphere::area() const {
  return 4 * M_PI * radius_ * radius_; //std::pow is more costly than doing the multiplication
}

float Sphere::volume() const {
  return 4 * M_PI * radius_ * radius_ * radius_ / 3;
}

std::ostream& Sphere::print(std::ostream& os) const {
  Shape::print(os);
  os << "Type: Sphere\n";
  os << "Center: (" << center_[0] << ", " << center_[1] << ", " << center_[2] << ")" << "\tRadius: " << radius_ << "\n";
  return os;
}

std::ofstream& Sphere::sdf_print(std::ofstream& ofs) const {
  ofs << "define shape sphere "
  << name_ << " "
  << center_[0] << " " << center_[1] << " " << center_[2] << " "
  << radius_ << " "
  << material_->name << " "
  << "\n";
  return ofs;
}


HitPoint Sphere::intersect(Ray const& ray) const {

  glm::vec3 normalized_direction = glm::normalize(ray.direction);
  float t = HUGE_VALF;

  bool is_intersected_distance = glm::intersectRaySphere(
    ray.origin,
    normalized_direction,
    center_,
    radius_ * radius_,
    t
  );
  
  glm::vec3 point = ray.origin + t * normalized_direction;

  return HitPoint{
    is_intersected_distance,
    t,
    name_,
    material_,
    point, // selbst berechnen (don't call twice)
    ray.direction
  };
}

glm::vec3 Sphere::get_normal(glm::vec3 const& point) const {
	return glm::normalize(glm::vec3{
	  point[0] - center_[0],
	  point[1] - center_[1],
	  point[2] - center_[2]
	});
}

