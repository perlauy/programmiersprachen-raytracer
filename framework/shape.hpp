#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "color.hpp"
#include "ray.hpp"
#include "hit_point.hpp"

#include <glm/vec3.hpp>
#include <string>

#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

class Shape {
  public: 

    Shape();
    Shape(std::string name, Color color);

    virtual ~Shape();
    // Without virtual, a Shape* s = new Sphere(), wont call ~Sphere

    virtual float area() const = 0;
    virtual float volume() const = 0;

    virtual HitPoint intersect(Ray const& ray) const = 0;

    virtual std::ostream& print(std::ostream& os) const;

  protected:
    std::string name_;
    Color color_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif
