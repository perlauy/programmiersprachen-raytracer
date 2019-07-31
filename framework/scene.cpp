#include "scene.hpp"

// !!!
// Creates a Material Dummy. Tested with others?
// Making it specific for materials
// Maybe we can overload it if needed?
/* template<typename T>
std::shared_ptr<T> find_name_in_set(std::string const& search_name, std::set<std::shared_ptr<T>> const& set) {
  // O(logN)
  // Must create a new material (temporary)
  std::shared_ptr<T> search_dummy = std::make_shared<T>(search_name, Color{}, Color{}, Color{}, 0.0f);
  auto it = set.find(search_dummy);
  return it == set.end() ?
    nullptr :
    *it;
}*/

Scene open_scene(std::string const& filename, RenderInformation& r) {

  std::cout << "- loading sdf - " << std::endl;

  std::string line_buffer;
  std::ifstream scene_file(filename);

  std::map<std::string, std::shared_ptr<Material>> materials;
  std::vector<std::shared_ptr<Shape>> shapes;
  std::vector<Light> lights;
  std::map<std::string, Camera> cameras;
  Color ambient{};

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
          materials.insert({material_name, new_material});

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

            std::shared_ptr<Material> material = materials.find(material_name)->second;

            Box box{shape_name, material, glm::vec3{x_min,y_min,z_min}, glm::vec3{x_max,y_max,z_max}};
            auto new_shape = std::make_shared<Box>(box);

            shapes.push_back(new_shape);

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

            std::shared_ptr<Material> material = materials.find(material_name)->second;

            Sphere sphere{shape_name, material, glm::vec3{x,y,z}, radius};
            auto new_shape = std::make_shared<Sphere>(sphere);

            shapes.push_back(new_shape);

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

          Light new_light{
            light_name,
            glm::vec3 { x, y, z },
            Color { r, g, b },
            brightness
          };

          lights.push_back(new_light);

          std::cout << "Light created: " << light_name << std::endl;


        } else if ("camera" == identifier) {
          std::string camera_name;
          line_string_stream >> camera_name;
          
          float fov_x;
          line_string_stream >> fov_x;

          float pos_x, pos_y, pos_z;
          line_string_stream >> pos_x;
          line_string_stream >> pos_y;
          line_string_stream >> pos_z;

          float dir_x, dir_y, dir_z;
          line_string_stream >> dir_x;
          line_string_stream >> dir_y;
          line_string_stream >> dir_z;

          float up_x, up_y, up_z;
          line_string_stream >> up_x;
          line_string_stream >> up_y;
          line_string_stream >> up_z;

          Camera camera{
            camera_name, 
            fov_x,
            glm::vec3{pos_x, pos_y, pos_z},
            glm::vec3{dir_x, dir_y, dir_z},
            glm::vec3{up_x, up_y, up_z}
          };

          cameras.insert({camera_name, camera});

          std::cout << "Camera created: " << camera_name << std::endl;


        } 
      } else if ("ambient" == identifier) {
          float r, g, b;
          line_string_stream >> r;
          line_string_stream >> g;
          line_string_stream >> b;

          ambient = {r, g, b};

          std::cout << "Ambient found: " << ambient << std::endl;

        } else if ("render" == identifier) {
        std::string camera_name;
        line_string_stream >> camera_name;
        Camera& camera = cameras.find(camera_name)->second;

        std::string file_name;
        line_string_stream >> file_name;
          
        unsigned int width;
        line_string_stream >> width;
        unsigned int height;
        line_string_stream >> height;

        r = RenderInformation{std::make_shared<Camera>(camera), file_name, width, height};

        std::cout << "Render Information loaded for: " << camera_name << std::endl;
        
      }
    // TODO: read last line with "render...." and return to references (?)
    }

    std::cout << "- file successfully loaded - " << std::endl << std::endl;

    // Since the object Scene is being created on return, when the function is over,
    // the memory is deleted. So the return type was changed.
    return Scene{materials, shapes, lights, ambient, cameras};

    scene_file.close();
  }

  else std::cout << "Unable to open file";

  return Scene{};
}