#define CATCH_CONFIG_RUNNER

// Project files
#include <material.hpp>
#include <scene.hpp>

// External libraries
#include <catch.hpp>

// Standard libraries
#include <memory>


// Aufgabe 7.1
// Create a new Scene object
TEST_CASE ("scene_default", "[scene]")
{
  Scene scene_default{};
  REQUIRE(scene_default.materials.size() == 0);
}

// Aufgabe 7.1
// Create a new Scene object with given materials
TEST_CASE ("scene_user_defined", "[scene]")
{
  std::set<std::shared_ptr<Material>> materials;

  auto material_blue = std::make_shared<Material>(
    "blue",
    Color{0.0, 0.0, 1.0},
    Color{0.0, 0.0, 1.0},
    Color{0.0, 0.0, 1.0},
    0.0
  );
  materials.insert(material_blue);

  auto material_red = std::make_shared<Material>(
    "red",
    Color{1.0, 0.0, 0.0},
    Color{1.0, 0.0, 0.0},
    Color{1.0, 0.0, 0.0},
    0.0
  );
  materials.insert(material_red);

  // Create scene using the materials set
  Scene scene_user_defined{materials};

  std::shared_ptr<Material> search_dummy = std::make_shared<Material>("red", Color{}, Color{}, Color{}, 0.0f);
  auto it = scene_user_defined.materials.find(search_dummy);

  REQUIRE(scene_user_defined.materials.size() == 2);
  std::cout << "Ka material red: " << (*it)->ka << std::endl;
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
