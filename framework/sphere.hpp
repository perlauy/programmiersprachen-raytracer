#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"

#include <glm/vec3.hpp>

class Sphere : public Shape {

  public:
    // Default constructor
    Sphere();

    // User-defined constructor
    Sphere(glm::vec3 const& center, unsigned float radius);

  private:
    glm::vec3 center_;
    unsigned float radius_;

}

#endif
