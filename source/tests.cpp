#define CATCH_CONFIG_RUNNER
#define _USE_MATH_DEFINES

#include <sphere.hpp>
#include <box.hpp>
#include <hit_point.hpp>

#include <memory>
#include <catch.hpp>
#include <cmath>
#include <iostream>

void printHitPoint(HitPoint hp) {
  if (hp.hit) {
    std::cout << "HitPoint: " << hp.object << std::endl;
    std::cout << "Distance: " << hp.t << "\t Point: (" << hp.point[0] << ", " << hp.point[1] << ", " << hp.point[2] <<")\n" << std::endl;
  } else {
    std::cout << "HitPoint missed\n" << hp.t << std::endl;
  }
};

TEST_CASE ("sphere", "[sphere]")
{
  Sphere sp0{};
  Sphere sp1{"SPHERE", {0.f,0.f,1.f}, {-10.f, -10.f, 10.f}, 5.f};
  REQUIRE (sp0.area() == Approx(4*M_PI));
  REQUIRE (sp0.volume() == Approx(4*M_PI/3));
  REQUIRE (sp1.area() == Approx(314.159));
  REQUIRE (sp1.volume() == Approx(523.599));
}

TEST_CASE ("box", "[box]")
{
  Box bx0{};
  Box bx1{"BOX", {1.f,0.f,0.f}, {-10.f, -10.f, 10.f}, {5.f, 0.f, 20.f}};
  REQUIRE (bx0.area() == Approx(6));
  REQUIRE (bx0.volume() == Approx(1));
  REQUIRE (bx1.area() == Approx(800));
  REQUIRE (bx1.volume() == Approx(1500));
}

TEST_CASE ("raycast", "[raycast]")
{
  Sphere sp1{"Athos", {1.f,0.f,0.f}, {0.f, 0.f, 0.f}, 5.f};
  Sphere sp2{"Porthos", {0.f,1.f,0.f}, {0.f, 0.f, 0.f}, 10.f};
  Sphere sp3{"Aramis", {0.f,0.f,1.f}, {-10.f, -10.f, -10.f}, 1.f};

  Ray ray1 = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}};
  Ray ray2 = {{-10.0f, 0.0f, 0.0f}, {10.0f, 0.0f, 0.0f}};
  Ray ray3 = {{0.0f, 0.0f, 0.0f}, {10.0f, 10.0f, 10.0f}};
  
  HitPoint sp1_ray1 = sp1.intersect(ray1);
  HitPoint sp1_ray2 = sp1.intersect(ray2);
  HitPoint sp1_ray3 = sp1.intersect(ray3);
  printHitPoint(sp1_ray1);
  printHitPoint(sp1_ray2);
  printHitPoint(sp1_ray3);
  REQUIRE(sp1_ray1.t == Approx(5));
  REQUIRE(sp1_ray2.t == Approx(5));
  REQUIRE(sp1_ray3.t == Approx(5));
  
  HitPoint sp2_ray1 = sp2.intersect(ray1);
  HitPoint sp2_ray2 = sp2.intersect(ray2);
  HitPoint sp2_ray3 = sp2.intersect(ray3);
  printHitPoint(sp2_ray1);
  printHitPoint(sp2_ray2);
  printHitPoint(sp2_ray3);
  REQUIRE(sp2_ray1.t == Approx(10));
  REQUIRE(sp2_ray2.t == Approx(20));
  REQUIRE(sp2_ray3.t == Approx(10));
  
  HitPoint sp3_ray1 = sp3.intersect(ray1);
  HitPoint sp3_ray2 = sp3.intersect(ray2);
  HitPoint sp3_ray3 = sp3.intersect(ray3);
  printHitPoint(sp3_ray1);
  printHitPoint(sp3_ray2);
  printHitPoint(sp3_ray3);
  REQUIRE(sp3_ray1.t == Approx(0));
  REQUIRE(sp3_ray2.t == Approx(0));
  REQUIRE(sp3_ray3.t == Approx(-16.3205));

}

int main(int argc, char *argv[])
{
  Sphere sp{"SPHERE", {0.f,0.f,1.f}, {-10.f, -10.f, 10.f}, 5.f};
  Box bx{"BOX", {1.f,0.f,0.f}, {-10.f, -10.f, 10.f}, {5.f, 0.f, 20.f}};
  std::cout << sp << std::endl;
  std::cout << bx << std::endl;

  Color red{255, 0, 0};
  glm::vec3 position{0.0f, 0.0f, 0.0f};
  std::shared_ptr<Sphere> s1 = std::make_shared<Sphere>("sphere0", red, position, 1.2f);
  std::shared_ptr<Shape> s2 = std::make_shared<Sphere>("sphere1", red, position, 1.2f);
  s1->print(std::cout);
  s2->print(std::cout);

  return Catch::Session().run(argc, argv);
}
