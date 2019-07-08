#define CATCH_CONFIG_RUNNER

#include "material.hpp"

#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>


void openScene(std::string const& filename) {
  std::string line;
  std::ifstream scene_file(filename);

  std::vector<std::shared_ptr<Material>> materials_vector;
  std::set<std::shared_ptr<Material>> materials_set;
  std::map<std::string, std::shared_ptr<Material>> materials_map;

  if (scene_file.is_open()) {

    while (std::getline(scene_file, line)) {

		std::vector<std::string> parameters{};
        split_line(line, parameters);

        std::copy(parameters.begin(), parameters.end(),
             std::ostream_iterator<std::string>(std::cout, "\n"));

        if(parameters.first() == "define") {
          
          std::vector<std::string> object_type = parameters.at(1);
          
          switch(object_type) {

            case "material":
              auto new_material = std::make_shared<Material>(parameters.at(2), parameters.at(3), parameters.at(4), parameters.at(5), parameters.at(6));
              materials_vector.push_back(new_material);
              break;

          }
        }
        // else "render"...{}

    }

    scene_file.close();
  }
  else cout << "Unable to open file";
}

void split_line(std::string const& str, std::vector result, char delim = '\t') {
    std::size_t current, previous = 0;
    current = str.find(delim);
    while (current != std::string::npos) {
        result.push_back(str.substr(previous, current - previous));
        previous = current + 1;
        current = str.find(delim, previous);
    }
    result.push_back(str.substr(previous, current - previous));
}




int main(int argc, char *argv[])
{
  openScene("scene.sdf");

}

