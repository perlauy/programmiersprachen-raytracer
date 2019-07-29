#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

int main(int argc, char* argv[])
{
  std::string sdf_path = "../../resources/scene.sdf";
  unsigned const image_width = 100;
  unsigned const image_height = 100;
  std::string const filename = "./checkerboard.ppm";
  if (argc > 1) {
    sdf_path = argv[1];
  }
  Scene scene_loaded = open_scene(sdf_path);

  //TODO: can't manage to make it work
  //Camera camera = find_name_in_set("eye", scene_loaded.cameras);
  Camera camera{"eye"};

  Renderer renderer{image_width, image_height, filename, scene_loaded, camera};

  //create separate thread to see updates of pixels while rendering
  std::thread render_thread([&renderer]() {renderer.render();});

  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }

  //"join" threads, i.e. synchronize main thread with render_thread
  render_thread.join();
  return 0;
}
