#include "box.hpp"


Box::Box() :
  minimum_{0.f,0.f,0.f}
  maximum_{1.f,1.f,1.f}
{}

Box::Box(glm::vec3 const& minimum, glm::vec3 const& maximum) :
  minimum_{minimum}
  maximum_{maximum}
{}


float Box::area() const override {
  return ((maximum[0] - minimum_[0]) + (maximum[1] - minimum_[1]) + (maximum[2] - minimum_[2])) * 2;
}

float Box::volume() const override {
  return (maximum[0] - minimum_[0]) * (maximum[1] - minimum_[1]) * (maximum[2] - minimum_[2]);
}