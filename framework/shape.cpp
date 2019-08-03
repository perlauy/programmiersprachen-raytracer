#include "shape.hpp"

Shape::Shape() :
  name_{"Anonymus"}
{ 
	material_ = nullptr;
}

Shape::Shape(std::string name, std::shared_ptr<Material> const& material) :
  name_{name},
  material_(material)
{
}

Shape::~Shape() {}

std::string Shape::get_name() const {
  return name_;
};

void Shape::scale(float mx, float my, float mz) {
  world_transformation_[0][0] += mx;
  world_transformation_[1][1] += my;
  world_transformation_[2][2] += mz;
}

void Shape::translate(float dx, float dy, float dz) {
  world_transformation_[3][0] += dx;
  world_transformation_[3][1] += dy;
  world_transformation_[3][2] += dz;
}

void Shape::rotate(float angle, float nx, float ny, float nz) {
  // float sum = nx + ny + nz;
  // nx = nx/sum;
  // ny = ny/sum;
  // nz = nz/sum;
  world_transformation_ += glm::rotate(angle, glm::vec3{nx, ny, nz});
}

void Shape::compute_world_transformation_inv_() {
  world_transformation_inv_ = glm::inverse(world_transformation_);
}

std::ostream& Shape::print(std::ostream& os) const {
  os << "Shape: " << name_ << "\n";
  if (material_ != nullptr) os << "Material: " << material_->name; else os << "No material defined";
  os << std::endl;
  return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
  std::ostream::sentry const cerberus(os);
  return cerberus ? s.print(os) : os;
}

std::ofstream& operator<<(std::ofstream& ofs, std::shared_ptr<Shape> const& s) {
  return s->sdf_print(ofs);
}


bool operator<(std::shared_ptr<Shape> const& lhs, std::shared_ptr<Shape> const& rhs) {
  return lhs->name_ < rhs->name_;
};

Ray transform_ray(glm::mat4 const& mat , Ray const& ray) {
  glm::vec3 new_origin = transform_point(mat, ray.origin);
  glm::vec3 new_direction = transform_point(mat, ray.direction);
  return Ray{new_origin, glm::normalize(new_direction)};
}

glm::vec3 transform_point(glm::mat4 const& mat , glm::vec3 const& vector) {
  glm::vec4 new_vector{vector, 1};
  new_vector = mat * new_vector;
  return glm::vec3{new_vector};
}