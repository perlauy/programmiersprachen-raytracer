// FoV
// -----------------------------------------------------------------------------
// DTO to represent the imaginary plane of the renderer, corresponding to the
// camera's field of view. It will be used to map the render pixels and generate
// the traceable rays.

#ifndef FOV_HPP
#define FOV_HPP

// External lbraries
#include <glm/vec3.hpp>

struct FoV {
  glm::vec3 min = {0.0f, 0.0f, -1.0f};
  glm::vec3 max = {1.0f, 1.0f, -1.0f};
};

#endif // #define FOV_HPP
