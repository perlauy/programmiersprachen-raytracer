#include "shape.hpp"
#include "color.hpp"

#include <string>

Shape::Shape() :
  name_{"Anonymus"},
  color_{.5f,.5f,.5f}
{ std::cout << "Constructor SHAPE" << std::endl; }

Shape::Shape(std::string name, Color color) :
  name_{name},
  color_{color}
{ std::cout << "Constructor SHAPE" << std::endl; }

Shape::~Shape() { std::cout << "Destructor SHAPE" << std::endl; }

std::ostream& Shape::print(std::ostream& os) const {
  os << "Shape: " << name_ << " of color (" << color_.r << ", " << color_.g << ", " << color_.b << ")\n";
  return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
  std::ostream::sentry const cerberus(os);
  return cerberus ? s.print(os) : os;
}
