#define CATCH_CONFIG_RUNNER
#define _USE_MATH_DEFINES

#include <catch.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

TEST_CASE ("intersect_ray_sphere", "[intersect]")
{
  // Ray
  glm::vec3 ray_origin{0.0f, 0.0f, 0.0f};
  // ray direction has to be normalized !
  // you can use :
  // v = glm :: normalize ( some_vector )
  glm::vec3 ray_direction{0.0f, 0.0f, 1.0f};
  // Sphere
  glm::vec3 sphere_center{0.0f, 0.0f, 5.0f};
  float sphere_radius{1.0f};
  float distance = 0.0f;
  auto result = glm::intersectRaySphere(
    ray_origin, ray_direction,
    sphere_center,
    sphere_radius * sphere_radius, // squared radius !!!
    distance);
  REQUIRE(distance == Approx (4.0f));
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
