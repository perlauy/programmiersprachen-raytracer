#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"

class Box : public Shape {

  public:
    // Default constructor
    Box();

    // User-defined constructor
    Box(std::string const& name, std::shared_ptr<Material> const& material, glm::vec3 const& minimum, glm::vec3 const& maximum);
    
    float area() const override;
    float volume() const override;

    HitPoint intersect(Ray const& ray) const override;

    std::ostream& print(std::ostream& os) const override;

  private:
    bool hit_test(HitPoint& result, Ray const& ray, float fixed_value, int index) const;

  private:
    glm::vec3 minimum_;
    glm::vec3 maximum_;

};


#endif
