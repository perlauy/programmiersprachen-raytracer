#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

int main(int argc, char* argv[])
{
  std::string sdf_path = "../../resources/scene.sdf";
  if (argc > 1) {
    sdf_path = argv[1];
  }

  RenderInformation info{};//{camera, filename, image_width, image_height};

  Scene scene_loaded = open_scene(sdf_path, info);

  Renderer renderer{info.width, info.height, info.filename, scene_loaded, info.camera}; //why de reference?

  //create separate thread to see updates of pixels while rendering
  //std::thread render_thread([&renderer]() {renderer.render();});

  renderer.render();

  Window window{{info.width, info.height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }

  //"join" threads, i.e. synchronize main thread with render_thread
  //render_thread.join();
  return 0;
}
