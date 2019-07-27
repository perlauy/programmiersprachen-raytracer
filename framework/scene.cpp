#include "scene.hpp"

template<typename T>
std::shared_ptr<T> find_name_in_set(std::string const& search_name, std::set<std::shared_ptr<T>> const& set) {
  // O(logN)
  // Must create a new material (temporary)
  std::shared_ptr<T> search_dummy = std::make_shared<T>(search_name, Color{}, Color{}, Color{}, 0.0f);
  auto it = set.find(search_dummy);
  return it == set.end() ?
    nullptr :
    *it;
}

Scene const& openScene(std::string const& filename) {
  std::string line_buffer;
  std::ifstream scene_file(filename);

  std::set<std::shared_ptr<Material>> materials;
  std::set<std::shared_ptr<Shape>> shapes;
  std::set<Light> lights;
  std::set<Camera> cameras;

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
          
      // Insert the material into the set
          materials.insert(new_material);

          std::cout << "Material created: " << material_name << std::endl;


        } else if ("shape" == identifier) {
          std::string type;
          line_string_stream >> type;

          std::string shape_name;
          line_string_stream >> shape_name;
          
          if ("box" == type) {
            float x_min, y_min, z_min;
            line_string_stream >> x_min;
            line_string_stream >> y_min;
            line_string_stream >> z_min;
            
            float x_max, y_max, z_max;
            line_string_stream >> x_max;
            line_string_stream >> y_max;
            line_string_stream >> z_max;

            std::string material_name;
            line_string_stream >> material_name;

            std::shared_ptr<Material> material = find_name_in_set(material_name, materials);

            Box box{shape_name, material, glm::vec3{x_min,y_min,z_min}, glm::vec3{x_max,y_max,z_max}};
            auto new_shape = std::make_shared<Shape>(box);

            shapes.insert(new_shape);

            std::cout << "Box created: " << shape_name << std::endl;

          } else if ("sphere" == type) {
            float x, y, z;
            line_string_stream >> x;
            line_string_stream >> y;
            line_string_stream >> z;

            float radius;
            line_string_stream >> radius;

            std::string material_name;
            line_string_stream >> material_name;

            std::shared_ptr<Material> material = find_name_in_set(material_name, materials);

            Sphere sphere{shape_name, material, glm::vec3{x,y,z}, radius};
            auto new_shape = std::make_shared<Shape>(sphere);

            shapes.insert(new_shape);

            std::cout << "Sphere created: " << shape_name << std::endl;
          }


        } else if ("light" == identifier) {
          std::string light_name;
          line_string_stream >> light_name;

          float x, y, z;
          line_string_stream >> x;
          line_string_stream >> y;
          line_string_stream >> z;

          float r, g, b;
          line_string_stream >> r;
          line_string_stream >> g;
          line_string_stream >> b;

          float brightness;
          line_string_stream >> brightness;

          Light new_lights{
            light_name,
            glm::vec3 { x, y, z },
            Color { r, g, b },
            brightness
          };

          lights.insert(new_lights);

          std::cout << "Light created: " << light_name << std::endl;


        } else if ("camera" == identifier) {
          std::string camera_name;
          line_string_stream >> camera_name;
          
          float fov_x;
          line_string_stream >> fov_x;

          Camera camera{
            camera_name, 
            fov_x
          };

          cameras.insert(camera);

          std::cout << "Camera created: " << camera_name << std::endl;
        }
      }

      return Scene{materials, shapes, lights, cameras};
    }

    scene_file.close();
  }

  else std::cout << "Unable to open file";
}