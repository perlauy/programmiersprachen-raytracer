// Project files
#include <scene.hpp>
#include <renderer.hpp>

// Standard libraries
#include <sstream>
#include <iomanip>
#include <thread>
#include <utility>

int main(int argc, char* argv[])
{
  std::string sdf_output_path = "../../output/animation/";
  unsigned const FPS = 24;

  unsigned const image_width = 800;
  unsigned const image_height = 600;
  std::string const output_path = "../../output/render/";  
  std::string const output_image_name = "bild%d.ppm";
  
  std::string sdf_path = "../../resources/scene.sdf";
  if (argc > 1) {
    sdf_path = argv[1];
  }

  RenderInformation info{};//{camera, filename, image_width, image_height};
  Scene scene_loaded = open_scene(sdf_path, info);
  std::string camera_name = info.camera->name;

  // Loop to render esch frame
  for (int t = 0; t / FPS < 2.0f; ++t) {
    // ANIMATE STH
    Camera& camera = scene_loaded.cameras.find(camera_name)->second;
    camera.direction[0] -= t / 1000.0f;

    // Get next scene file name
    std::ostringstream os;
    os << std::setfill('0') << std::setw(5) << t;
    // Define the name of the image output for this sdf file
    info.filename = output_path +  "bild_" + os.str() + ".ppm";

    write_scene(sdf_output_path + "scene_" + os.str() + ".sdf", scene_loaded, info);
  }

  for (int t = 0; t / FPS < 2.0f; ++t) {
    std::ostringstream os;
    os << std::setfill('0') << std::setw(5) << t;
    RenderInformation info{};

    Scene scene_loaded = open_scene(sdf_output_path +  "scene_" + os.str() + ".sdf", info);

    Renderer renderer{info.width, info.height, output_path + info.filename, scene_loaded, info.camera};

    std::thread render_thread([&renderer]() {renderer.render();});

    render_thread.join();
  }

  return 0;
}
