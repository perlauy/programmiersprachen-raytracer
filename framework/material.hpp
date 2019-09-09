#ifndef MATERIAL_HPP
#define MATERIAL_HPP

// Project files
#include "color.hpp"

// Standard libraries
#include <memory>
#include <string>
#include <fstream>
#include <sstream>


struct Material {

  friend std::ostream& operator<<(std::ostream& os, Material const& m)
  {
    os << m.name << ": " << m.ka << "\t" << m.kd << "\t" << m.ks << "\t" << m.m << "\n";
    return os;
  }

  friend std::ofstream& operator<<(std::ofstream& ofs, Material const& m)
  {
    ofs << "define material "
    << m.name << " "
    << m.ka.r << " " << m.ka.g << " " << m.ka.b << " "
    << m.kd.r << " " << m.kd.g << " " << m.kd.b << " "
    << m.ks.r << " " << m.ks.g << " " << m.ks.b << " "
    << m.m << "\n";
    return ofs;
  }
  
  Material() {
  };
  
  Material(std::string const& arg_name, Color const& arg_ka, Color const& arg_kd, Color const& arg_ks, float arg_m, float ri, float o) : 
	  name{arg_name},
	  ka{arg_ka},
	  kd{arg_kd},
	  ks{arg_ks},
	  m{arg_m},
    refractive_index{ri},
    opacity{o}
  {};

  friend bool operator<(std::shared_ptr<Material> const& lhs, std::shared_ptr<Material> const& rhs) {
    return lhs->name < rhs->name;
  };

  std::string name = "";
  Color ka{0.0f, 0.0f, 0.0f};
  Color kd{0.0f, 0.0f, 0.0f};
  Color ks{0.0f, 0.0f, 0.0f};
  float m = 0.0f;
  float refractive_index = 1.0f;
  float opacity = 1.0f;

};

#endif
