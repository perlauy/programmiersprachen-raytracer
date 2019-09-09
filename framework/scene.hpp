#ifndef SCENE_HPP
#define SCENE_HPP

// Project files
#include <camera.hpp>
#include <light.hpp>
#include <material.hpp>
#include <shape.hpp>
#include <sphere.hpp>
#include <box.hpp>
#include <color.hpp>
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

/**
  * Takes a destination file path and a scene object, and saves it as SDF
  * @param filepath (std::string const&) full path to which to save the file
  * @param scene (Scene) scene object to save as SDF
  * @param render_info (RenderInformation) object with the necessary information
  * @return int 0 if it was saved, 1 if some error was encountered
  */
int write_scene(std::string const& filepath, Scene const& scene, RenderInformation const& render_info);
int write_scene(std::string const& filepath, Scene const& scene, std::vector<std::string> const& transform_strings, RenderInformation const& render_info);

#endif //#define SCENE_HPP
