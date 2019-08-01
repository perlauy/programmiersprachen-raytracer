#ifndef CAMERA_HPP
#define CAMERA_HPP

// External libraries
#include <glm/vec3.hpp>

// Standard libraries
#include <string>
#include <fstream>
#include <sstream>


struct Camera {

  friend std::ofstream& operator<<(std::ofstream& ofs, Camera const& c)
  {
    ofs << "define camera "
    << c.name << " "
    << c.fov_x << " " 
    << c.position[0] << " " << c.position[1] << " " << c.position[2] << " "
    << c.direction[0] << " " << c.direction[1] << " " << c.direction[2] << " "
    << c.up[0] << " " << c.up[1] << " " << c.up[2] << "\n";
    return ofs;
  }
  
  friend bool operator<(Camera const& lhs, Camera const& rhs) {
    return lhs.name < rhs.name;
  };

  std::string name = "";
  float fov_x = 60.0; // 0 to 180
  glm::vec3 position = {0.0f, 0.0f, 0.0f};
  glm::vec3 direction = {0.0f, 0.0f, -1.0f};
  glm::vec3 up = {0.0f, 1.0f, 0.0f};

};

#endif //#define CAMERA_HPP
