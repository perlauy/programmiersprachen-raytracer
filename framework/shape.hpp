#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/ulp.hpp>
#include <glm/gtx/vector_angle.hpp>


// Project files
#include "color.hpp"
#include "hit_point.hpp"
#include "material.hpp"
#include "ray.hpp"

// External libraries
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

// Standard libraries
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>


class Shape {
  public: 

    Shape();
    Shape(std::string name, std::shared_ptr<Material> const& material);

    virtual ~Shape();
    // Without virtual, a Shape* s = new Sphere(), wont call ~Sphere

    virtual float area() const = 0;
    virtual float volume() const = 0;

    virtual std::string get_name() const;

    virtual HitPoint intersect(Ray const& ray) const = 0;
    virtual glm::vec3 get_normal(glm::vec3 const& point) const = 0;

    virtual void scale(float mx, float my, float mz);
    virtual void translate(float dx, float dy, float dz);
    virtual void rotate(float degree, float nx, float ny, float nz);

    virtual void compute_world_transformation_inv_();

    virtual std::ostream& print(std::ostream& os) const;
    virtual std::ofstream& sdf_print(std::ofstream& ofs) const = 0;

    friend bool operator<(std::shared_ptr<Shape> const& lhs, std::shared_ptr<Shape> const& rhs);

  protected:
    std::string name_;
    std::shared_ptr<Material> material_;
    glm::mat4 world_transformation_{1};
    glm::mat4 world_transformation_inv_{1};
};

std::ostream& operator<<(std::ostream& os, Shape const& s);
std::ofstream& operator<<(std::ofstream& ofs, std::shared_ptr<Shape> const& s);
Ray transform_ray(glm::mat4 const& mat , Ray const& ray);
glm::vec3 transform_point(glm::mat4 const& mat , glm::vec3 const& point);
glm::vec3 transform_vector(glm::mat4 const& mat , glm::vec3 const& vector);

#endif
