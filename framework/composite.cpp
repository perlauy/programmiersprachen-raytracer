#include "composite.hpp"


Composite::Composite() :
  Shape()
{}

Composite::Composite(std::string const& name) :
  Shape(name, nullptr)
{}

Composite::~Composite() {}

float Composite::area() const {
  float area = 0.0f;
  for (auto child : children_) {
    area += child->area();
  }
  return area;
}

float Composite::volume() const {
  float volume = 0.0f;
  for (auto child : children_) {
    volume += child->volume();
  }
  return volume;
}

std::ostream& Composite::print(std::ostream& os) const {
  Shape::print(os);
  os << "COMPOSITE: " << name_ << "\n";
  for (auto child : children_) {
    child->print(os);
  };
  os << "-----------------\n";
  return os;
}

HitPoint Composite::intersect(Ray const& original_ray) const {
	HitPoint result{};
	Ray transformed_ray{
	  transform_point(Shape::world_transformation_inv_, original_ray.origin),
	  glm::normalize(transform_vector(Shape::world_transformation_inv_, original_ray.direction))
	};

	for (auto child : children_) {
		HitPoint hp = child->intersect(transformed_ray);
		if (hp.t < result.t) {
			result = hp;
		};
	};

  result.point = transform_point(Shape::world_transformation_, result.point);
  result.normal = glm::normalize(transform_vector(glm::transpose(Shape::world_transformation_inv_), result.normal));

	return result;
};

std::vector<std::shared_ptr<Shape>> Composite::get_children() const {
	return children_;
};

glm::vec3 Composite::get_normal(glm::vec3 const& world_point) const {
	// Remove this method, since it will be included in HitPoint struct
	return {0.0f,1.0f,0.0f};
};


void Composite::add(std::shared_ptr<Shape> const& s) {
  children_.push_back(s);
};

void Composite::remove(std::shared_ptr<Shape> const& s) {
  auto it = children_.begin(); ; 
  while ((*it)->get_name() != s->get_name()) ++it;
  children_.erase(it);

};

