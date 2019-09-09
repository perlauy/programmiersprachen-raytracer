#include "triangle.hpp"

		#include <ostream>
		std::ostream& print_vec(std::ostream& os, glm::vec3 const& c)
  	{
    	os << "(" << c.r << "," << c.g << "," << c.b << ")\n";
    	return os;
  	}

// Default constructor
Triangle::Triangle() :
  Shape(),
  vert0_{0.0f,0.0f,0.0f},
  vert1_{1.0f,0.0f,0.0f},
  vert2_{0.0f,1.0f,0.0f}
  {}

// User-defined constructor
Triangle::Triangle(std::string const& name, std::shared_ptr<Material> const& material,
  glm::vec3 const& vert0, glm::vec3 const& vert1, glm::vec3 const& vert2) :
  Shape(name, material),
  vert0_{vert0},
  vert1_{vert1},
  vert2_{vert2}
  {}

Triangle::~Triangle() {}

float Triangle::area() const {
  return glm::length(glm::cross((vert0_-vert1_),(vert0_ - vert2_)));
  }

float Triangle::volume() const {
  return 0;
  }

std::ostream& Triangle::print(std::ostream& os) const {
  Shape::print(os);
  os << "Type: Triangle\n";
  os << "Point A: ";
  print_vec(os,vert0_) << "\n";
  os << "Point B: ";
  print_vec(os,vert1_) << "\n";
  os << "Point C: ";
  print_vec(os, vert2_) << "\n" << "\n";
  return os;
}

HitPoint Triangle::intersect(Ray const& original_ray) const {
  Ray trans_ray = transform_ray(Shape::world_transformation_inv_, original_ray);
  glm::vec3 bary_result;
  glm::vec3 normalized_direction = glm::normalize(trans_ray.direction);
  float ratio = trans_ray.direction[0] / normalized_direction[0];

  bool is_intersected_distance = glm::intersectRayTriangle(
    trans_ray.origin,
    normalized_direction,
    vert0_,
    vert1_,
    vert2_,
    bary_result
  );

 // if (is_intersected_distance) std::cout << "Kugel";
  
  glm::vec3 resulting_point = trans_ray.origin + bary_result.z * ratio * trans_ray.direction;

  return HitPoint{
    is_intersected_distance,
    bary_result.z ,
    name_,
    material_,
    transform_point(Shape::world_transformation_, resulting_point),
    original_ray.direction
  };
};

glm::vec3 Triangle::get_normal(glm::vec3 const& point) const {
  glm::vec3 normal = glm::normalize(glm::cross((vert0_ - vert1_), (vert0_ - vert2_)));
  return glm::normalize(transform_vector(glm::transpose(Shape::world_transformation_inv_), normal));
}
