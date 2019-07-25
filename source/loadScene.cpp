#define CATCH_CONFIG_RUNNER

// Project files
#include <material.hpp>

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


std::vector<std::shared_ptr<Material>> materials_vector;
std::set<std::shared_ptr<Material>> materials_set;
std::map<std::string, std::shared_ptr<Material>> materials_map;

void openScene(std::string const& filename) {
  std::string line_buffer;
  std::ifstream scene_file(filename);

  if (scene_file.is_open()) {

    while(std::getline(scene_file, line_buffer) ) {

      std::istringstream line_string_stream(line_buffer);

      std::string identifier;
      line_string_stream >> identifier;
    // gets the next string, separated by a white space

      if("define" == identifier) {
        line_string_stream >> identifier;

        if("material" == identifier) {
          std::string material_name;
          line_string_stream >> material_name;

          float ka_red, ka_green, ka_blue;
          line_string_stream >> ka_red;
          line_string_stream >> ka_green;
          line_string_stream >> ka_blue;
       
          float kd_red, kd_green, kd_blue;
          line_string_stream >> kd_red;
          line_string_stream >> kd_green;
          line_string_stream >> kd_blue;

          float ks_red, ks_green, ks_blue;
          line_string_stream >> ks_red;
          line_string_stream >> ks_green;
          line_string_stream >> ks_blue;

          float material_m;
          line_string_stream >> material_m;
       
      // Create the shared pointer to the new material
      // (MateriaL{}) to avoid constructor
          auto new_material = std::make_shared<Material>(
            material_name,
            Color { ka_red, ka_green, ka_blue },
            Color { kd_red, kd_green, kd_blue },
            Color { ks_red, ks_green, ks_blue },
            material_m
          );
          
      // Insert the material in the three different containers
          materials_vector.push_back(new_material);
          materials_set.insert(new_material);
          materials_map.insert(make_pair(material_name, new_material));

          std::cout << "Material created: " << material_name << std::endl;
        }
      }
    }

    scene_file.close();
  }

  else std::cout << "Unable to open file";
}


std::shared_ptr<Material> find_material_in_vector(std::string const& search_name) {
  // O(N)
  // Must visit each element secuentially until it finds the right one

  auto it = std::find_if(materials_vector.begin(), materials_vector.end(),
    [search_name](std::shared_ptr<Material> const& material) -> bool { return search_name == material->name; }
  );
  return it == materials_vector.end() ?
    nullptr :
    *it;
}

std::shared_ptr<Material> find_material_in_set(std::string const& search_name) {
  // O(logN)
  // Must create a new material (temporary)
  std::shared_ptr<Material> search_dummy = std::make_shared<Material>(search_name, Color{}, Color{}, Color{}, 0.0f);
  auto it = materials_set.find(search_dummy);
  return it == materials_set.end() ?
    nullptr :
    *it;
}

std::shared_ptr<Material> find_material_in_map(std::string const& search_name) {
  // O(logN)
  // It is not needed to save a temporary material, but it requires saving the keys.
  // So it may require more memory than a set?

  auto it = materials_map.find(search_name);
  return it == materials_map.end() ?
    nullptr :
    it->second;
}


int main(int argc, char *argv[])
{
  // Load scene
  openScene("scene.sdf");

  // Search for material "blue" in vector
  auto blue_vector_result = find_material_in_vector("blue");
  std::cout << "Searched for 'blue' in vector, got: " << std::endl;
  if (blue_vector_result != nullptr) {
    std::cout << *blue_vector_result << std::endl;
    } else {
    std::cout << "nothing"<< std::endl;
    }
  std::cout << std::endl;
  
  // Search for material "blue" in set
  auto blue_set_result = find_material_in_set("blue");
  std::cout << "Searched for 'blue' in vector, got: " << std::endl;
  if (blue_set_result != nullptr) {
    std::cout << *blue_set_result << std::endl;
    } else {
    std::cout << "nothing"<< std::endl;
    }
  std::cout << std::endl;

  // Search for material "blue" in map
  auto blue_map_result = find_material_in_map("blue");
  std::cout << "Searched for 'blue' in vector, got: " << std::endl;
  if (blue_map_result != nullptr) {
    std::cout << *blue_map_result << std::endl;
    } else {
    std::cout << "nothing"<< std::endl;
    }
  std::cout << std::endl;


  // Search for material "black" in vector
  auto black_vector_result = find_material_in_vector("black");
  std::cout << "Searched for 'black' in vector, got: " << std::endl;
  if (black_vector_result != nullptr) {
    std::cout << *black_vector_result << std::endl;
    } else {
    std::cout << "nothing"<< std::endl;
   }
  std::cout << std::endl;

  // Search for material "black" in set
  auto black_set_result = find_material_in_set("black");
  std::cout << "Searched for 'black' in vector, got: " << std::endl;
  if (black_set_result != nullptr) {
    std::cout << *black_set_result << std::endl;
    } else {
    std::cout << "nothing"<< std::endl;
    }
  std::cout << std::endl;

  // Search for material "black" in map
  auto black_map_result = find_material_in_map("black");
  std::cout << "Searched for 'black' in map, got: " << std::endl;
  if (black_map_result != nullptr) {
    std::cout << black_map_result << std::endl;
    } else {
    std::cout << "nothing"<< std::endl;
    }
  std::cout << std::endl;
  
}

