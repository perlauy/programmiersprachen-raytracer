#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include "color.hpp"

#include <glm/vec3.hpp>
#include <string>

class Sphere : public Shape {

  public:
    // Default constructor
    Sphere();

    // User-defined constructor
    Sphere(std::string name, Color color, glm::vec3 const& center, float radius);

    float area() const override;
    float volume() const override;

  private:
    glm::vec3 center_;
    float radius_;

};

#endif