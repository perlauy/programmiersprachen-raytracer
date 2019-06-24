#include "shape.hpp"
#include "color.hpp"

#include <string>

Shape::Shape() :
  name_{"Anonymus"},
  color_{.5f,.5f,.5f}
{}

Shape::Shape(std::string name, Color color) :
  name_{name},
  color_{color}
{}
