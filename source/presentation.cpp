// Project files
#include <scene.hpp>
#include <renderer.hpp>

// External libraries
#include <windows.h>
#include <fileapi.h>

// Standard libraries
#include <sstream>
#include <iomanip>
#include <thread>
#include <utility>



int main(int argc, char* argv[])
{
  unsigned const FPS = 6;
  std::string const VERSION = "001";

  std::string const output_path = "../../output/presentation/render/" + VERSION + "/";
  std::string sdf_output_path = "../../output/presentation/scene/" + VERSION + "/";
  
  // CREATE SCENE
  std::map<std::string, std::shared_ptr<Material>> materials{};
  std::vector<std::shared_ptr<Shape>> shapes{};
  std::vector<Light> lights{};
  Color ambient{0.1f, 0.1f, 0.1f};
  std::vector<std::string> transform_strings{};

  // Create materials
  auto glass = std::make_shared<Material>(
    "glass",
    Color{0.0f, 0.0f, 0.0f},
    Color{0.9f, 1.0f, 1.0f},
    Color{0.5f, 0.5f, 0.5f},
    1.0f,
    1.4f,
    0.4f
  );

  // Create shapes
  // (will animate with transform strings)
  //Box box{shape_name, material, glm::vec3{x_min,y_min,z_min}, glm::vec3{x_max,y_max,z_max}};
  Sphere glass_ball{"glass_ball", glass, glm::vec3{0.0f,0.0f,-50.0f}, 5.0f};
  auto glass_ball_ptr = std::make_shared<Sphere>(glass_ball);

  // Create lights
  Light back_light{
    "back_light",
    glm::vec3{0.0f, 0.0f, -120.0f},
    Color{1.0f, 1.0f, 0.9f},
    5.0f
  };

  // Create camera
  Camera eye{
    "eye", 
    60.0f,
    glm::vec3{0.0f, 0.0f, 0.0f},
    glm::vec3{0.0f, 0.0f, -1.0f},
    glm::vec3{0.0f, 1.0f, 0.0f}
  };

  materials.insert({"glass", glass});
  shapes.push_back(glass_ball_ptr);
  lights.push_back(back_light);
  
  auto camera_ptr = std::make_shared<Camera>(eye);
  RenderInformation info{camera_ptr, "", 800, 600};

  // SAVE SDF
  for (int t = 0; t / FPS < 5.0f; ++t) {
    // ANIMATE CAMERA
    camera_ptr->position[1] += t / 10.0f;

    std::map<std::string, Camera> cameras{};
    cameras.insert({"eye", *camera_ptr});

    // CREATE TRANSFORMS


    Scene frame_scene{materials, shapes, lights, ambient, cameras};

    // Get next scene file name
    std::ostringstream os;
    os << std::setfill('0') << std::setw(5) << t;

    // Define the name of the image output for this sdf file
    if (CreateDirectory(output_path.c_str(), NULL) || // <- This is a WINAPI method. Check for Linux
      ERROR_ALREADY_EXISTS == GetLastError())
    {
      info.filename = output_path +  "bild_" + os.str() + ".ppm";
    }

    if (CreateDirectory(sdf_output_path.c_str(), NULL) || // <- This is a WINAPI method. Check for Linux
      ERROR_ALREADY_EXISTS == GetLastError())
    {
      write_scene(sdf_output_path + "scene_" + os.str() + ".sdf", frame_scene, transform_strings, info);
    }
  }

  // BATCH RENDER
  for (int t = 0; t / FPS < 5.0f; ++t) {
    std::ostringstream os;
    os << std::setfill('0') << std::setw(5) << t;
    RenderInformation info{};

    Scene scene_loaded = open_scene(sdf_output_path +  "scene_" + os.str() + ".sdf", info);

    Renderer renderer{info.width, info.height, info.filename, scene_loaded, info.camera};

    std::thread render_thread([&renderer]() {renderer.render();});

    render_thread.join();
  }

  return 0;
}
