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

HitPoint Sphere::intersect(Ray const& original_ray) const {

  Ray trans_ray = transform_ray(Shape::world_transformation_inv_, original_ray);
  float t = HUGE_VALF;
  //glm::vec3 normalized_direction = glm::normalize(trans_ray.direction);
  //float ratio = trans_ray.direction[0] / normalized_direction[0];

  bool is_intersected_distance = glm::intersectRaySphere(
    trans_ray.origin,
    trans_ray.direction,
    center_,
    radius_ * radius_,
    t
  );

  if (is_intersected_distance) std::cout << "Kugel";
  
  glm::vec3 resulting_point = trans_ray.origin + t * trans_ray.direction;

  return HitPoint{
    is_intersected_distance,
    t,
    name_,
    material_,
    transform_point(Shape::world_transformation_, resulting_point),
    original_ray.direction//transform_vector(Shape::world_transformation_, trans_ray.direction)
  };
}

glm::vec3 Sphere::get_normal(glm::vec3 const& world_point) const {
  glm::vec3 point = transform_point(Shape::world_transformation_inv_, world_point);
	glm::vec3 normal = glm::normalize(glm::vec3{
	  point[0] - center_[0],
	  point[1] - center_[1],
	  point[2] - center_[2]
	});
  std::cout <<"[ " << normal[0] << ", " << normal[1] << ", " << normal[2]  << " ]" << std::endl;
  return glm::normalize(transform_vector(glm::transpose(Shape::world_transformation_inv_), normal));
}

