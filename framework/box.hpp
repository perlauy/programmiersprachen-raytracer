#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"

#include <glm/vec3.hpp>

class Box : public Shape {

  public:
    // Default constructor
    Box();

    // User-defined constructor
    Box(glm::vec3 const& minimum, glm::vec3 const& maximum);

  private:
    glm::vec3 minimum_;
    glm::vec3 maximum_;

}


#endif
