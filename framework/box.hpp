#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"
#include "color.hpp"

#include <glm/vec3.hpp>
#include <string>

class Box : public Shape {

  public:
    // Default constructor
    Box();

    // User-defined constructor
    Box(std::string name, Color color, glm::vec3 const& minimum, glm::vec3 const& maximum);
    
    float area() const override;
    float volume() const override;
    
  private:
    glm::vec3 minimum_;
    glm::vec3 maximum_;

};


#endif