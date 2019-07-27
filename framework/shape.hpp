#ifndef SHAPE_HPP
#define SHAPE_HPP

// header, system
#include <iostream>
#include <ostream>
#include <string>
#include <memory>
#include <cmath>

// header, external libraries
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/intersect.hpp>

// header, project
#include "color.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "hit_point.hpp"


class Shape {
  public: 

    Shape();
    Shape(std::string name, std::shared_ptr<Material> const& material);

    // Default constructor
    virtual ~Shape();
    // Without virtual, a Shape* s = new Sphere(), wont call ~Sphere

    virtual float area() const = 0;
    virtual float volume() const = 0;

    virtual HitPoint intersect(Ray const& ray, float& t) const = 0;

    virtual std::ostream& print(std::ostream& os) const;

  protected:
    std::string name_;
    std::shared_ptr<Material> material_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif
