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

      p.color = trace(r); 

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
  Ray transformed_ray{r.origin, glm::vec3(r_T)};
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
Color Renderer::trace(Ray const& r) const {
  
  // Create a default hit point, which will have the info
  HitPoint hp{};
  std::shared_ptr<Shape> s;  

  for(auto it = scene_.objects.begin(); it != scene_.objects.end(); ++it) {
    HitPoint result = (*it)->intersect(r/* s->apply_world_transformation(r)*/);
    if (result.hit && result.t < hp.t) {
      hp = result;
      s = *it;
    }
  }

  // Now that we know which object and which material is, calculate light
  // TODO
  std::shared_ptr<Material> mat = hp.material_;


  if (hp.hit && mat != nullptr) {
    return shade(s, hp);
    //return mat->ka;
  } else {
    // TODO: define background color    
    return Color{1.0f,1.0f,0.6f};
  }

};

// computes color out of object and hitpoint
Color Renderer::shade(std::shared_ptr<Shape> const& s, HitPoint const& hp) const {
  // Do we simply add every light? It will be HDR, so we don't cap it?
  Color result{0.0f, 0.0f, 0.0f};

  // Calculate for each light
  for(auto light_it = scene_.lights.begin(); light_it != scene_.lights.end(); ++light_it) {

    glm::vec3 normal = s->get_normal(hp.point);

    // Get ray l and angle n_r 
    glm::vec3 l = glm::normalize(light_it->pos - hp.point);
    // float angle normal,l
    float angle = glm::angle(normal, l);

    // glm::vec3 r = glm::reflect(l, normal);
    glm::vec3 v = glm::normalize(-hp.direction);

    // (loop the objects and see if l intersects with another object)
    bool visable = true;
    for(auto it = scene_.objects.begin(); it != scene_.objects.end(); ++it) {
      if (*it != s) {
        Ray r{hp.point, l};
        HitPoint result = (*it)->intersect(r);
        if (result.hit && result.t > 0) visable = false;
      }
    }

    if (visable) {
      
      // DIFFUSE LIGHT
      // Ip * kd (l·n)
      float angle_l_normal = glm::angle(l, normal);
      if (0 <= std::cos(angle_l_normal)) {
        Color diffuse_light{
          light_it->brightness * light_it->color.r * hp.material_->kd.r * std::cos(angle_l_normal),
          light_it->brightness * light_it->color.g * hp.material_->kd.g * std::cos(angle_l_normal),
          light_it->brightness * light_it->color.b * hp.material_->kd.b * std::cos(angle_l_normal)
        };
        result += diffuse_light;
        // Phong
        // TODO: reflection. test
        //intensity[i] += light_it->brightness * hp.material_->ks * std::pow(std::cos(hp.material_->ks,v), m)
        glm::vec3 reflect_vector = 2*glm::dot(normal,l)*normal - l;
        float ref_fact = std::pow(glm::dot(reflect_vector, v), hp.material_->m);
        Color reflect_light{
          light_it->brightness * light_it->color.r * hp.material_->ks.r * ref_fact,
          light_it->brightness * light_it->color.g * hp.material_->ks.g * ref_fact,
          light_it->brightness * light_it->color.b * hp.material_->ks.b * ref_fact
        };
        result += reflect_light;
      }
      
    }
  }

  // AMBIENT LIGHT
  Color ambient_light{
    scene_.ambient.r * hp.material_->ka.r,
    scene_.ambient.g * hp.material_->ka.g,
    scene_.ambient.b * hp.material_->ka.b
  };

  result += ambient_light;

  return result;
}
