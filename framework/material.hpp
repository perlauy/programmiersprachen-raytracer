#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"
#include <string>

struct Material {

  friend std::ostream& operator<<(std::ostream& os, Material const& m)
  {
    os << m.name << ": " << m.ka << "\t" << m.kd << "\t" << m.ks << "\t" << m.m << "\n";
    return os;
  }

  std::string name = "";
  Color ka{0.0f, 0.0f, 0.0f};
  Color kd{0.0f, 0.0f, 0.0f};
  Color ks{0.0f, 0.0f, 0.0f};
  float m = 0.0f;

};

#endif
