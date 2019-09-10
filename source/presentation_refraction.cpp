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
  unsigned const FPS = 10;
  std::string const VERSION = "002";

  std::string const output_path = "../../output/presentation/render/" + VERSION + "/";
  std::string sdf_output_path = "../../output/presentation/scene/" + VERSION + "/";
  
  // CREATE SCENE
  std::map<std::string, std::shared_ptr<Material>> materials{};
  std::vector<std::shared_ptr<Shape>> shapes{};
  std::vector<Light> lights{};
  Color ambient{0.3f, 0.3f, 0.3f};
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
    Color{0.0f, 0.0f, 1.0f},
    Color{0.0f, 0.0f, 1.0f},
    Color{0.0f, 0.0f, 1.0f},
    10.0f,
    1.0f,
    1.0f
  );
  auto cb = std::make_shared<Material>(
    "cb",
    Color{0.5f, 0.5f, 0.5f},
    Color{0.5f, 0.5f, 0.5f},
    Color{0.5f, 0.5f, 0.5f},
    10.0f,
    1.04f,
    1.0f
  );
  materials.insert({"glass", glass});
  materials.insert({"green", green});
  materials.insert({"ca", ca});
  materials.insert({"cb", cb});

  // Create shapes
  // (will animate with transform strings)
  Box s1{"s1", ca, {-25, -15, -50}, {0, -10, -25} };
  Box s3{"s3", cb, {-25, -15, -75}, {0, -10, -50} };
  Box s5{"s5", ca, {-25, -15, -100}, {0, -10, -75} };
  Box s7{"s7", cb, {-25, -15, -125}, {0, -10 ,-100} };
  Box s9{"s9", ca, {-25, -15, -150}, {0, -10 ,-125} };
  Box s2{"s2", cb, {0, -15, -50}, {25, -10, -25} };
  Box s4{"s4", ca, {0, -15, -75}, {25, -10, -50} };
  Box s6{"s6", cb, {0, -15, -100}, {25, -10, -75} };
  Box s8{"s8", ca, {0, -15, -125}, {25, -10 ,-100} };
  Box s10{"s10", cb, {0, -15, -150}, {25, -10 ,-125} };
  auto s1_ptr = std::make_shared<Box>(s1);
  auto s3_ptr = std::make_shared<Box>(s3);
  auto s5_ptr = std::make_shared<Box>(s5);
  auto s7_ptr = std::make_shared<Box>(s7);
  auto s9_ptr = std::make_shared<Box>(s9);
  auto s2_ptr = std::make_shared<Box>(s2);
  auto s4_ptr = std::make_shared<Box>(s4);
  auto s6_ptr = std::make_shared<Box>(s6);
  auto s8_ptr = std::make_shared<Box>(s8);
  auto s10_ptr = std::make_shared<Box>(s10);
  shapes.push_back(s1_ptr);
  shapes.push_back(s2_ptr);
  shapes.push_back(s3_ptr);
  shapes.push_back(s4_ptr);
  shapes.push_back(s5_ptr);
  shapes.push_back(s6_ptr);
  shapes.push_back(s7_ptr);
  shapes.push_back(s8_ptr);
  shapes.push_back(s9_ptr);
  shapes.push_back(s10_ptr);

  Sphere glass_ball{"glass_ball", green, glm::vec3{7.0f,-3.0f,-40.0f}, 5.0f};
  auto glass_ball_ptr = std::make_shared<Sphere>(glass_ball);
  shapes.push_back(glass_ball_ptr);

  // Create lights
/*  Light back_light{
    "back_light",
    glm::vec3{0.0f, 0.0f, -120.0f},
    Color{1.0f, 1.0f, 0.9f},
    5.0f
  };
  lights.push_back(back_light);
*/
  Light sun{
    "sun",
    glm::vec3{100.0f, 700.0f, -0.0f},
    Color{0.2f, 0.5f, 0.2f},
    10.0f
  };
  lights.push_back(sun);

  Light behind{
    "behind",
    glm::vec3{100.0f, 10.0f, 0.0f},
    Color{0.2f, 0.2f, 0.6f},
    10.0f
  };
  lights.push_back(behind);


  // Create camera
  Camera eye{
    "eye", 
    60.0f,
    glm::vec3{0.0f, 0.0f, 0.0f},
    glm::vec3{0.0f, 0.0f, -1.0f},
    glm::vec3{0.0f, 1.0f, 0.0f}
  };
  auto camera_ptr = std::make_shared<Camera>(eye);

  transform_strings.push_back("transform glass_ball scale 1.5 1.2 1");
  
  RenderInformation info{camera_ptr, "", 800, 600};
 
  float center_z = -40.0f;
  // SAVE SDF
  for (int t = 0; t / FPS < 5.0f; ++t) {
    // ANIMATE CAMERA
    //camera_ptr->position[1] += t / 10.0f;
    center_z -= t / 10.0f;
    glass_ball_ptr->change_center(glm::vec3{7.0f,-3.0f,center_z});

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
