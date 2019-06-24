#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "color.hpp"
#include <string>

class Shape {
  public: 

    Shape();
    Shape(std::string name, Color color);

    virtual float area() const = 0;
    virtual float volume() const = 0;

  private:
    std::string name_;
    Color color_;
};

#endif
