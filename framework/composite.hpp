#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

// Project files
#include "shape.hpp"

// Standard libraries
#include <vector>


class Composite : public Shape {

  public:
    // Default constructor
    Composite();

    // User-defined constructor
    Composite(std::string const& name);
    ~Composite();

    float area() const override;
    float volume() const override;

    std::ostream& print(std::ostream& os) const override;

    HitPoint intersect(Ray const& ray) const override;
    glm::vec3 get_normal(glm::vec3 const& point) const override;

    void add(std::shared_ptr<Shape> const& s);
    void remove(std::shared_ptr<Shape> const& s);
    std::vector<std::shared_ptr<Shape>> get_children() const;

  private:
    std::vector<std::shared_ptr<Shape>> children_;
};

#endif
