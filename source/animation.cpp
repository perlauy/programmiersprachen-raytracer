#include <scene.hpp>

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

  info.filename = "scene_001.ppm";
  //write_scene(sdf_output_path + "scene_001.sdf", scene_loaded, info);
  write_scene("./scene_001.sdf", scene_loaded, info);


  return 0;
}
