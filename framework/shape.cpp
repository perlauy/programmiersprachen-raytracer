#include "shape.hpp"

Shape::Shape() :
  name_{"Anonymus"}
{ 
	material_ = std::make_shared<Material>();
}

Shape::Shape(std::string name, std::shared_ptr<Material> const& material) :
  name_{name}  
{
  std::shared_ptr<Material> material_(material);
}

Shape::~Shape() {}

std::ostream& Shape::print(std::ostream& os) const {
  os << "Shape: " << name_ << "\n";
  return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
  std::ostream::sentry const cerberus(os);
  return cerberus ? s.print(os) : os;
}

bool operator<(std::shared_ptr<Shape> const& lhs, std::shared_ptr<Shape> const& rhs) {
  return lhs->name_ < rhs->name_;
};