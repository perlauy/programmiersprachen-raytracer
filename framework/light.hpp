#ifndef LIGHT_HPP
#define LIGHT_HPP

// Standard libraries
#include <string>


struct Light {
  // TO BE IMPLEMENTED

  friend bool operator<(std::shared_ptr<Light> const& lhs, std::shared_ptr<Light> const& rhs) {
    return lhs->name < rhs->name;
  };

  std::string name = "";

};

#endif //#define LIGHT_HPP
