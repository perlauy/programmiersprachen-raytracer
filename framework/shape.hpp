#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "color.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "hit_point.hpp"

#include <iostream>
#include <string>
#include <memory>
#include <glm/vec3.hpp>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

class Shape {
  public: 

    Shape();
    Shape(std::string name, std::shared_ptr<Material> const& material);

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
