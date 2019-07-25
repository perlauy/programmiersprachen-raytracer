#define CATCH_CONFIG_RUNNER

// Project files
#include <box.hpp>
#include <camera.hpp>
#include <material.hpp>
#include <light.hpp>
#include <scene.hpp>
#include <shape.hpp>
#include <sphere.hpp>

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
  // Create a set of materials
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

  // Create a set of shapes
  auto sp0 = std::make_shared<Sphere>("sphere0", material_blue, glm::vec3{-10.f, -10.f, 10.f}, 5.f);
  auto bx0 = std::make_shared<Box>("box0", material_red, glm::vec3{-10.f, -10.f, 10.f}, glm::vec3{5.f, 0.f, 20.f});
  std::set<std::shared_ptr<Shape>> objects = {sp0, bx0};

  // Create a set of lights
  auto light = std::make_shared<Light>(Light{"light0"});
  std::set<std::shared_ptr<Light>> lights = {light};

  // Create a set of cameras
  auto camera = std::make_shared<Camera>(Camera{"camera0"});
  std::set<std::shared_ptr<Camera>> cameras = {camera};


  // Create scene using the sets
  Scene scene_user_defined{materials, objects, lights, cameras};

  // Test operator< by seaching for a material
  auto search_dummy_material = std::make_shared<Material>("red", Color{}, Color{}, Color{}, 0.0f);
  auto it_material = scene_user_defined.materials.find(search_dummy_material);

  // Test operator< by seaching for a shape objects
  auto search_dummy_shape = std::make_shared<Box>("box0", material_red, glm::vec3{}, glm::vec3{});
  auto it_shape = scene_user_defined.objects.find(search_dummy_shape);

  REQUIRE(scene_user_defined.materials.size() == 2);
  std::cout << "Ka material red: " << (*it_material)->ka << std::endl;
  (*it_shape)->print(std::cout);
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
