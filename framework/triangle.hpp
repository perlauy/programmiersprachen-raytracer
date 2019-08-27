#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"


class Triangle : public Shape {

  public:
    // Default constructor
    Triangle();

    // User-defined constructor
    Triangle(std::string const& name, std::shared_ptr<Material> const& material, glm::vec3 const& vert0, glm::vec3 const& vert1, glm::vec3 const& vert2);
    ~Triangle();

    float area() const override;
    float volume() const override;

    std::ostream& print(std::ostream& os) const override;

    HitPoint intersect(Ray const& ray) const override;
    glm::vec3 get_normal(glm::vec3 const& point) const override;

  private:
    glm::vec3 center_;
    float radius_;

};

#endif
