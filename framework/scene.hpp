#ifndef SCENE_HPP
#define SCENE_HPP

// Project files
#include <camera.hpp>
#include <light.hpp>
#include <material.hpp>
#include <shape.hpp>
#include <sphere.hpp>
#include <box.hpp>

// Standard libraries
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <vector>
#include <sstream>
#include <string>
#include <memory>
#include <vector>


struct Scene {

  std::map<std::string, std::shared_ptr<Material>> materials{};
  std::vector<std::shared_ptr<Shape>> objects{};
  std::vector<Light> lights{};
  std::map<std::string, Camera> cameras{};

};

//template<typename T>
//std::shared_ptr<T> find_name_in_set(std::string const& search_name, std::set<std::shared_ptr<T>> const& set);

Scene open_scene(std::string const& filename);

#endif //#define SCENE_HPP
