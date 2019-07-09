#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char** argv) {
  
  // Clarify how to use this file
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <sdf_file.sdf>" << std::endl;
    return 1;
  }

  std::string line_buffer;
  std::ifstream in_scene_file(argv[1]);

  while(std::getline(in_scene_file, line_buffer)) {

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

        std::cout << "Material loaded: " << material_name << std::endl;

      }
    }
  }


  in_scene_file.close();
}