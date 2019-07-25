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
  
  Material() {

  };
  Material(std::string const& arg_name, Color const& arg_ka, Color const& arg_kd, Color const& arg_ks, float arg_m) : 
	  name{arg_name},
	  ka{arg_ka},
	  kd{arg_kd},
	  ks{arg_ks},
	  m{arg_m}
  {};

  friend bool operator<(std::shared_ptr<Material> const& lhs, std::shared_ptr<Material> const& rhs) {
    return lhs->name < rhs->name;
  };

  std::string name = "";
  Color ka{0.0f, 0.0f, 0.0f};
  Color kd{0.0f, 0.0f, 0.0f};
  Color ks{0.0f, 0.0f, 0.0f};
  float m = 0.0f;

};

#endif
