#ifndef CAMERA_HPP
#define CAMERA_HPP

// Standard libraries
#include <string>


struct Camera {
  // TO BE IMPLEMENTED
  
  friend bool operator<(std::shared_ptr<Camera> const& lhs, std::shared_ptr<Camera> const& rhs) {
    return lhs->name < rhs->name;
  };

  std::string name = "";

};

#endif //#define CAMERA_HPP
