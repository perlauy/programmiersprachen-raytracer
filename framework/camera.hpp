#ifndef CAMERA_HPP
#define CAMERA_HPP

// Standard libraries
#include <string>


struct Camera {
  // TO BE IMPLEMENTED
  
  friend bool operator<(Camera const& lhs, Camera const& rhs) {
    return lhs.name < rhs.name;
  };

  std::string name = "";

};

#endif //#define CAMERA_HPP
