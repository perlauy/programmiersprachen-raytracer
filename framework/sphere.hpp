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
    std::ofstream& sdf_print(std::ofstream& ofs) const override;

    HitPoint intersect(Ray const& ray) const override;
    glm::vec3 get_normal(glm::vec3 const& point) const override;

  private:
    glm::vec3 center_;
    float radius_;

};

#endif
