#ifndef SCENE_HPP
#define SCENE_HPP

// Project files
#include <camera.hpp>
#include <light.hpp>
#include <material.hpp>
#include <shape.hpp>
#include <sphere.hpp>
#include <box.hpp>
#include <render_information.hpp>

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


struct Scene {

  std::map<std::string, std::shared_ptr<Material>> materials{};
  std::vector<std::shared_ptr<Shape>> objects{};
  std::vector<Light> lights{};
  Color ambient{0.0f, 0.0f, 0.0f};
  std::map<std::string, Camera> cameras{};
  
};

//template<typename T>
//std::shared_ptr<T> find_name_in_set(std::string const& search_name, std::set<std::shared_ptr<T>> const& set);

Scene open_scene(std::string const& filename, RenderInformation& r);

#endif //#define SCENE_HPP
