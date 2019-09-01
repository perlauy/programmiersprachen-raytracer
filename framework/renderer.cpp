// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------
#define _USE_MATH_DEFINES
#include "renderer.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file, Scene const& s, Camera const& c) :
  width_(w),
  height_(h),
  color_buffer_(w*h, Color{0.0, 0.0, 0.0}),
  filename_(file),
  ppm_(width_, height_),
  scene_(s),
  camera_(c)
{}

void Renderer::render()
{
  std::size_t const checker_pattern_size = 20;

  glm::mat4 camera_transform_matrix{};

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      // Get a ray according to camera world
      Ray simple_ray = compute_camera_ray(p); 

      // Multiply simple camera ray by camera matrix transform
      // TODO: test camera movements
      Ray r = transform_ray_to_world(simple_ray, camera_transform_matrix);

      p.color = trace(r, 1);

      // HDR to LDR
      //float c_sum = (p.color.r+ p.color.b + p.color.g)/3;
      //p.color = p.color * ((c_sum)/(c_sum + 1));

      // HDR to LDR
      p.color = Color{
      p.color.r / (p.color.r + 1),
      p.color.g / (p.color.g + 1),
      p.color.b / (p.color.b + 1)
      };
      
      
      write(p);
    }
  }
  ppm_.save(filename_);
  std::cout << "DONE" << std::endl;
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}

// computes the ray from eye to pixel
Ray Renderer::compute_camera_ray(Pixel const& p) const {
  float fov_distance = (width_ / 2.0f) / std::tan(camera_.fov_x * M_PI / 360.0f);
  glm::vec3 direction{p.x - (width_ / 2.0f), p.y - (height_ / 2.0f), -fov_distance};
  Ray r{camera_.position, glm::normalize(direction)};
  return r;
};

// transformation of ray by given transformation matrix
Ray Renderer::transform_ray_to_world(Ray const& r, glm::mat4 const& matrix) const {
  glm::vec4 r_T{ r.direction[0], r.direction[1], r.direction[2], 1};
  r_T = matrix * r_T; 
  Ray transformed_ray{r.origin, glm::normalize(glm::vec3(r_T))};
  return transformed_ray;
};

// generates transformation matrix
glm::mat4 Renderer::get_camera_matrix() const {
  glm::vec3 vector_n{0,0,-1};
  glm::vec3 vector_u = glm::normalize(camera_.up) * vector_n;
  vector_u = glm::normalize(vector_u);
  glm::vec3 vector_v = vector_u * vector_n;
  vector_v = glm::normalize(vector_v);

  glm::mat4 matrix{
    {vector_u[0], vector_v[0], -vector_n[0], camera_.position[0]},
    {vector_u[1], vector_v[1], -vector_n[1], camera_.position[1]},
    {vector_u[2], vector_v[2], -vector_n[2], camera_.position[2]},
    {0, 0, 0, 1}
  };
  return matrix;
};

// test ray on intersection
Color Renderer::trace(Ray const& r, float priority) const {
  float epsilon = 0.01;
  
  if (priority > 0.01) {
  // Create a default hit point, which will have the info
    HitPoint hp{};
    std::shared_ptr<Shape> s;  

    for(auto it = scene_.objects.begin(); it != scene_.objects.end(); ++it) {
      HitPoint result = (*it)->intersect(r);
      if (result.hit && result.t > epsilon && result.t < hp.t + epsilon) {
        hp = result;
        s = *it;
      }
    }

    // Now that we know which object and which material is, calculate light
    std::shared_ptr<Material> mat = hp.material_;

    if (hp.hit && mat != nullptr) {
      if (mat->opacity < 1) {
        Color opaque = shade(s, hp) * mat->opacity; 

        float normal_ray_angle, incoming_index, outgoing_index;
        glm::vec3 rotation_axis;

        if (hp.incident) {
          normal_ray_angle = glm::angle(-r.direction, hp.normal);// - M_PI / 2;
          incoming_index = 1;
          outgoing_index = mat->refractive_index;
          rotation_axis = glm::normalize(glm::cross(-r.direction, hp.normal));
        } else {
          normal_ray_angle = glm::angle(r.direction, hp.normal);// - M_PI / 2;
          incoming_index = mat->refractive_index;
          outgoing_index = 1;
          rotation_axis = glm::normalize(glm::cross(r.direction, hp.normal));
        }

        float refracted_angle = std::asin(incoming_index * std::sin(normal_ray_angle) / outgoing_index);
        glm::mat4 rotation_matrix = glm::rotate(normal_ray_angle - refracted_angle, rotation_axis);

        // Material where the medium is
        // TODO: consider nested materials

        glm::vec3 refracted_direction = glm::normalize(transform_vector(rotation_matrix, r.direction)); 

        // Move the consecutive raycasting a bit to avoid re-intersecting the same point
        // (solve transparent sphere noise)
        glm::vec3 delta_new_hp = hp.normal * (hp.incident ? -0.0001f : 0.0001f);

        Color transparent = trace(Ray{hp.point + delta_new_hp, refracted_direction}, priority * (1 - mat->opacity)) * (1 - mat->opacity);
        return opaque + transparent;
        
      } else return shade(s, hp);
    } 

  }

  return Color{0.0f,0.0f,0.0f};

};

// computes color out of object and hitpoint
Color Renderer::shade(std::shared_ptr<Shape> const& s, HitPoint const& hp) const {
  
  Color result{0.0f, 0.0f, 0.0f};

  // Calculate for each light
  for(auto light_it = scene_.lights.begin(); light_it != scene_.lights.end(); ++light_it) {


    // Get ray l and angle n - r 
    glm::vec3 l = glm::normalize(light_it->pos - hp.point);
    float angle = glm::angle(hp.normal, l);
    glm::vec3 v = glm::normalize(-hp.direction);

    // (loop the objects and see if l intersects with another object)

    float light_amount = 1;
    for(auto it = scene_.objects.begin(); it != scene_.objects.end(); ++it) {
      if (*it != s) {
        Ray r{hp.point, l};
        HitPoint result = (*it)->intersect(r);
        if (result.hit && result.t > 0.01) {
          light_amount *= (1 - result.material_->opacity);
        }
      }
    }

    if (light_amount > 0.01) {

      float angle_l_normal = glm::angle(l, hp.normal);
      
      if (0 <= std::cos(angle_l_normal)) {
        // DIFFUSE LIGHT
        // Ip * kd (l·n)
        Color diffuse_light{
          light_it->brightness * light_it->color.r * hp.material_->kd.r * std::cos(angle_l_normal),
          light_it->brightness * light_it->color.g * hp.material_->kd.g * std::cos(angle_l_normal),
          light_it->brightness * light_it->color.b * hp.material_->kd.b * std::cos(angle_l_normal)
        };
        result += diffuse_light * light_amount;

        // REFLECTION
        // Ip * ks (r·v)^m
        glm::vec3 reflect_vector = 2*glm::dot(hp.normal,l)*hp.normal - l;
        float ref_fact = std::pow(glm::dot(reflect_vector, v), hp.material_->m);
        Color reflect_light{
          light_it->brightness * light_it->color.r * hp.material_->ks.r * ref_fact,
          light_it->brightness * light_it->color.g * hp.material_->ks.g * ref_fact,
          light_it->brightness * light_it->color.b * hp.material_->ks.b * ref_fact
        };
        result += reflect_light * light_amount;
      }
      
    }
  }

  // AMBIENT LIGHT
  // Ia * ka
  Color ambient_light{
    scene_.ambient.r * hp.material_->ka.r,
    scene_.ambient.g * hp.material_->ka.g,
    scene_.ambient.b * hp.material_->ka.b
  };

  result += ambient_light;

  return result;
};
