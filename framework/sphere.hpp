#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"

class Sphere : public Shape {

  public:
    // Default constructor
    Sphere();

    // User-defined constructor
    Sphere(std::string const& name, std::shared_ptr<Material> const& material, glm::vec3 const& center, float radius);
    ~Sphere();

    float area() const override;
    float volume() const override;

    std::ostream& print(std::ostream& os) const override;

    HitPoint intersect(Ray const& ray, float& t) const override;
    
  private:
    glm::vec3 center_;
    float radius_;

};

#endif
