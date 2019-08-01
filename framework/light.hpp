#ifndef LIGHT_HPP
#define LIGHT_HPP

// Project files
#include "color.hpp"

// External libraries
#include <glm/vec3.hpp>

// Standard libraries
#include <string>
#include <fstream>
#include <sstream>

struct Light {
  
  friend std::ofstream& operator<<(std::ofstream& ofs, Light const& l)
  {
    ofs << "define light "
    << l.name << " "
    << l.pos[0] << " " << l.pos[1] << " " << l.pos[2] << " "
    << l.color.r << " " << l.color.g << " " << l.color.b << " "
    << l.brightness << " "
    << "\n";
    return ofs;
  }

  friend bool operator<(Light const& lhs, Light const& rhs) {
    return lhs.name < rhs.name;
  };

  std::string name = "";
  glm::vec3 pos{};
  Color color{};
  float brightness = 0;

};

#endif //#define LIGHT_HPP
