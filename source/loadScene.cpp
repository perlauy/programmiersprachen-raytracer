#define CATCH_CONFIG_RUNNER

#include <material.hpp>

#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <iterator>

void openScene(std::string const& filename) {
  std::string line_buffer;
  std::ifstream scene_file(filename);

  std::vector<std::shared_ptr<Material>> materials_vector;
  std::set<std::shared_ptr<Material>> materials_set;
  std::map<std::string, std::shared_ptr<Material>> materials_map;

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
          Color material_ka{ka_red, ka_green, ka_blue};
       
          float kd_red, kd_green, kd_blue;
          line_string_stream >> kd_red;
          line_string_stream >> kd_green;
          line_string_stream >> kd_blue;
          Color material_kd{kd_red, kd_green, kd_blue};

          float ks_red, ks_green, ks_blue;
          line_string_stream >> ks_red;
          line_string_stream >> ks_green;
          line_string_stream >> ks_blue;
          Color material_ks{ks_red, ks_green, ks_blue};

          float material_m;
          line_string_stream >> material_m;
       
          auto new_material = std::make_shared<Material>(material_name, material_ka, material_kd, material_ks, material_m);
          
          materials_vector.push_back(new_material);
		  std::cout << "Material created: " << material_name << std::endl;
        }
      }
    }

    scene_file.close();
  }

  else std::cout << "Unable to open file";
}





int main(int argc, char *argv[])
{
	openScene("scene.sdf");

}

