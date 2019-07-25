#ifndef SCENE_HPP
#define SCENE_HPP

// Project files
#include <camera.hpp>
#include <light.hpp>
#include <material.hpp>
#include <shape.hpp>

// Standard libraries
#include <memory>
#include <set>


struct Scene {
  
  std::set<std::shared_ptr<Material>> materials{};
  std::set<std::shared_ptr<Shape>> objects{};
  
  std::set<Light> lights{};
  std::set<Camera> cameras{};

};

#endif //#define SCENE_HPP
