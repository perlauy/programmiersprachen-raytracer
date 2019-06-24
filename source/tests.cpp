#define CATCH_CONFIG_RUNNER
#define _USE_MATH_DEFINES

#include <sphere.hpp>
#include <box.hpp>

#include <catch.hpp>
#include <cmath>


TEST_CASE ("sphere", "[sphere]")
{
  Sphere sp0{};
  Sphere sp1{{-10.f, -10.f, 10.f}, 5.f};
  REQUIRE (sp0.area() == Approx(4*M_PI));
  REQUIRE (sp0.volume() == Approx(4*M_PI/3));
  REQUIRE (sp1.area() == Approx(314.159));
  REQUIRE (sp1.volume() == Approx(523.599));
}

TEST_CASE ("box", "[box]")
{
  Box bx0{};
  Box bx1{{-10.f, -10.f, 10.f}, {5.f, 0.f, 20.f}};
  REQUIRE (bx0.area() == Approx(6));
  REQUIRE (bx0.volume() == Approx(1));
  REQUIRE (bx1.area() == Approx(800));
  REQUIRE (bx1.volume() == Approx(1500));
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
