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
  unsigned const FPS = 24;
  std::string const VERSION = "008";

  std::string const output_path = "../../output/presentation/render/" + VERSION + "/";
  std::string sdf_output_path = "../../output/presentation/scene/" + VERSION + "/";
  
  // CREATE SCENE
  std::map<std::string, std::shared_ptr<Material>> materials{};
  std::vector<std::shared_ptr<Shape>> shapes{};
  std::vector<Light> lights{};
  Color ambient{0.3f, 0.3f, 0.3f};
  std::vector<std::string> transform_strings{};

  // Create materials
  auto white = std::make_shared<Material>(
    "white",
    Color{1.0f, 1.0f, 1.0f},
    Color{1.0f, 1.0f, 1.0f},
    Color{0.0f, 0.0f, 0.0f},
    0.0f,
    1.0f,
    1.0f
  );
  auto black = std::make_shared<Material>(
    "black",
    Color{0.0f, 0.0f, 0.0f},
    Color{0.0f, 0.0f, 0.0f},
    Color{0.0f, 0.0f, 0.0f},
    0.0f,
    1.0f,
    1.0f
  );
  auto glass = std::make_shared<Material>(
    "glass",
    Color{0.0f, 0.0f, 0.05f},
    Color{0.4f, 0.4f, 0.35f},
    Color{1.0f, 1.0f, 0.9f},
    100.0f,
    1.4f,
    0.4f
  );
  auto dark = std::make_shared<Material>(
    "dark",
    Color{0.0f, 0.0f, 0.0f},
    Color{0.0f, 0.04f, 0.06f},
    Color{0.0f, 0.8f, 0.95f},
    30.0f,
    1.0f,
    1.0f
  );

  auto green = std::make_shared<Material>(
    "green",
    Color{0.0f, 1.0f, 0.0f},
    Color{0.0f, 1.0f, 0.0f},
    Color{0.0f, 1.0f, 0.0f},
    90.0f,
    1.5f,
    0.4f
  );
  auto ca = std::make_shared<Material>(
    "ca",
    Color{0.2f, 0.3f, 0.9f},
    Color{0.2f, 0.3f, 0.9f},
    Color{0.2f, 0.3f, 0.9f},
    10.0f,
    1.0f,
    1.0f
  );
  auto cb = std::make_shared<Material>(
    "cb",
    Color{0.95f, 0.95f, 0.2f},
    Color{0.95f, 0.95f, 0.2f},
    Color{0.95f, 0.95f, 0.2f},
    10.0f,
    1.0f,
    1.0f
  );
  auto cc = std::make_shared<Material>(
    "cc",
    Color{1.0f, 0.95f, 0.1f},
    Color{1.0f, 0.95f, 0.1f},
    Color{1.0f, 0.95f, 0.1f},
    10.0f,
    1.0f,
    1.0f
  );
  auto cd = std::make_shared<Material>(
    "cd",
    Color{0.15f, 0.3f, 0.9f},
    Color{0.15f, 0.3f, 0.9f},
    Color{0.15f, 0.3f, 0.9f},
    10.0f,
    1.4f,
    1.0f
  );
  materials.insert({"glass", glass});
  materials.insert({"green", green});
  materials.insert({"dark", dark});
  materials.insert({"white", white});
  materials.insert({"ca", ca});
  materials.insert({"cb", cb});
  materials.insert({"cc", cc});
  materials.insert({"cd", cd});

  // Create shapes
  // (will animate with transform strings)
  Box s1{"s1", ca, {-20, -20, -20}, {0, 20, 0} };
  Box s2{"s2", cb, {-20, -20, 0}, {0, 20, 20} };
  Box s3{"s3", cc, {0, -20, -20}, {20, 20, 0} };
  Box s4{"s4", cd, {0, -20, 0}, {20, 20, 20} };
  auto s1_ptr = std::make_shared<Box>(s1);
  auto s2_ptr = std::make_shared<Box>(s2);
  auto s3_ptr = std::make_shared<Box>(s3);
  auto s4_ptr = std::make_shared<Box>(s4);
  shapes.push_back(s1_ptr);
  shapes.push_back(s2_ptr);
  shapes.push_back(s3_ptr);
  shapes.push_back(s4_ptr);
  Composite cube{"cube"};
  cube.add(s1_ptr);
  cube.add(s2_ptr);
  cube.add(s3_ptr);
  cube.add(s4_ptr);
  auto cube_ptr = std::make_shared<Composite>(cube);
  shapes.push_back(cube_ptr);

  Sphere glass_ball{"glass_ball", glass, glm::vec3{0.0f,1.0f,-60.0f}, 10.0f};
  auto glass_ball_ptr = std::make_shared<Sphere>(glass_ball);
  shapes.push_back(glass_ball_ptr);
  Sphere opaque_ball{"opaque_ball", dark, glm::vec3{0.0f,-2.0f,-30.0f}, 11.0f};
  auto opaque_ball_ptr = std::make_shared<Sphere>(opaque_ball);
  shapes.push_back(opaque_ball_ptr);

  // Create lights
  Light back_light{
    "back_light",
    glm::vec3{0.0f, -50.0f, -120.0f},
    Color{1.0f, 0.95f, 0.9f},
    1.0f
  };
  lights.push_back(back_light);

  Light sun{
    "sun",
    glm::vec3{0.0f, 700.0f, 0.0f},
    Color{0.5f, 0.5f, 0.5f},
    6.0f
  };
  lights.push_back(sun);


  // Create camera
  Camera eye{
    "eye", 
    60.0f,
    glm::vec3{0.0f, 0.0f, 0.0f},
    glm::vec3{0.0f, 0.0f, -1.0f},
    glm::vec3{0.0f, 1.0f, 0.0f}
  };
  auto camera_ptr = std::make_shared<Camera>(eye);

  transform_strings.push_back("transform opaque_ball translate 0 0 0");
  transform_strings.push_back("transform glass_ball translate 0 0 0");
  transform_strings.push_back("transform cube translate 0 0 -200");
  transform_strings.push_back("transform cube rotate 0 0 1 0");
  transform_strings.push_back("transform cube rotate 25 1 0 0");

  RenderInformation info{camera_ptr, "", 960, 540};
 
  float move_y_opaque = 0.0f;
  float move_y_glass = 0.0f;
  float rotate_cube = 0.0f;
  // SAVE SDF
  for (int t = 0; t / FPS < 10.0f; ++t) {
    // Move camera upwards
    // 1 cicle = 5 seconds = FPS * 5
    camera_ptr->position[2] -= std::sin(t / (FPS * 5.0f)) * 0.01f;
    
    // Move ball a bit downwards
	  move_y_opaque -= std::sin(t / (FPS * 5.0f)) * 2;
	  move_y_glass += std::sin(t / (FPS * 5.0f)) * std::sin(t / (FPS * 5.0f)) * 0.4;
	  transform_strings.clear();
    transform_strings.push_back("transform opaque_ball translate 0 " + std::to_string(move_y_opaque) + " 0");
    transform_strings.push_back("transform glass_ball translate 0 " + std::to_string(move_y_glass) + " 0");

    rotate_cube += t * 0.2;
    transform_strings.push_back("transform cube translate 0 0 -200");
    transform_strings.push_back("transform cube rotate " + std::to_string(rotate_cube) + " 0 1 0");
    transform_strings.push_back("transform cube rotate 15 1 0 0");

    std::map<std::string, Camera> cameras{};
    cameras.insert({"eye", *camera_ptr});

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
  for (int t = 0; t / FPS < 10.0f; ++t) {
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
