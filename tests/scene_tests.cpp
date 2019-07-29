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
#include <map>

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
// TEST_CASE ("scene_user_defined", "[scene]")
// {
// // Create a set of materials
// std::map<std::string, std::shared_ptr<Material>> materials;

// auto material_blue = std::make_shared<Material>(
// "blue",
// Color{0.0, 0.0, 1.0},
// Color{0.0, 0.0, 1.0},
// Color{0.0, 0.0, 1.0},
// 0.0
// );
// materials.insert({"blue", material_blue});

// auto material_red = std::make_shared<Material>(
// "red",
// Color{1.0, 0.0, 0.0},
// Color{1.0, 0.0, 0.0},
// Color{1.0, 0.0, 0.0},
// 0.0
// );
// materials.insert({"red", material_red});

// // Create a set of shapes
// auto sp0 = std::make_shared<Sphere>("sphere0", material_blue, glm::vec3{-10.f, -10.f, 10.f}, 5.f);
// auto bx0 = std::make_shared<Box>("box0", material_red, glm::vec3{-10.f, -10.f, 10.f}, glm::vec3{5.f, 0.f, 20.f});
// std::set<std::shared_ptr<Shape>> objects = {sp0, bx0};

// // Create a set of lights
// Light light{"light0"};
// std::set<Light> lights = {light};

// // Create a set of cameras
// Camera camera{"camera0"};
// std::set<Camera> cameras = {camera};
// std::cout << materials.size();

// // Create scene using the sets
// //Scene scene_user_defined{materials, objects, lights, cameras};

// // Test operator< by seaching for a material
// std::shared_ptr<Material> search_dummy_material = std::make_shared<Material>("red", Color{}, Color{}, Color{}, 0.0f);
// auto it_material = scene_user_defined.materials.find(search_dummy_material);

// // Test operator< by seaching for a shape objects
// auto search_dummy_shape = std::make_shared<Box>("box0", material_red, glm::vec3{}, glm::vec3{});
// auto it_shape = scene_user_defined.objects.find(search_dummy_shape);

// REQUIRE(materials.size() == 2);
// std::cout << "SIZE: "<< scene_user_defined.materials.size() << std::endl;
// std::cout << "Ka material red: " << (*it_material)->ka << std::endl;
// std::cout << "Ka material red: " << *it_material << std::endl;
// (*it_shape)->print(std::cout);

// REQUIRE(scene_user_defined.materials.size() == 2);

// }
/*
// Aufgabe 7.1
// Load a scene
TEST_CASE ("scene_load", "[scene]")
{
  Scene scene_loaded = open_scene("scene.sdf");

  REQUIRE(scene_loaded.materials.size() == 3);
  REQUIRE(scene_loaded.objects.size() == 2);
  REQUIRE(scene_loaded.lights.size() == 1);
  REQUIRE(scene_loaded.cameras.size() == 1);

  // Test operator< by seaching for a material
  std::shared_ptr<Material> search_dummy_material = std::make_shared<Material>("red", Color{}, Color{}, Color{}, 0.0f);
  auto it_material = scene_loaded.materials.find(search_dummy_material);
  std::cout << "Material: " << *(*it_material) << std::endl;
  // Test operator< by seaching for a shape objects
  auto search_dummy_shape = std::make_shared<Box>("rbottom", *it_material, glm::vec3{}, glm::vec3{});
  auto it_shape = scene_loaded.objects.find(search_dummy_shape);

  (*it_shape)->print(std::cout);
}

 */
int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}