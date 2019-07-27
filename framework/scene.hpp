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
#include <set>
#include <sstream>
#include <string>
#include <memory>
#include <set>


struct Scene {

  std::set<std::shared_ptr<Material>> materials{};
  std::set<std::shared_ptr<Shape>> objects{};
  std::set<Light> lights{};
  std::set<Camera> cameras{};

};

std::shared_ptr<T> find_name_in_set(std::string const& search_name, std::set<std::shared_ptr<T>> const& set);

Scene const& openScene(std::string const& filename);

#endif //#define SCENE_HPP
