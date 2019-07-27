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

  FoV fov = compute_fov();

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      Ray r = compute_camera_ray(p);
      p.color = trace(r);

      /*
      if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
        p.color = Color{0.0f, 1.0f, float(x)/height_};
      } else {
        p.color = Color{1.0f, 0.0f, float(y)/width_};
      }
      */

      write(p);
    }
  }
  ppm_.save(filename_);
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


FoV Renderer::compute_fov() const {

  float fov_distance = (width_ / 2.0f) / std::tan(camera_.angle * M_PI / 360);
  std::cout << "fov_distance: \n" << fov_distance << std::endl;
  std::cout << "fov_distance: \n" << camera_.angle << std::endl;

  glm::vec3 normalized_direction = glm::normalize(camera_.direction);
  glm::vec3 fov_center = camera_.position + normalized_direction * fov_distance;
  float angle = -90.0f;
  glm::mat4 identity_matrix{};
  glm::vec4 camera_up_T{ camera_.up[0], camera_.up[1], camera_.up[2], 0 };
  glm::vec4 normalized_direction_T{ normalized_direction[0], normalized_direction[1], normalized_direction[2], 0 };

  glm::mat4 matrix_rotate_left = glm::rotate(angle, camera_.up);

  glm::vec4 direction_left = normalized_direction_T * matrix_rotate_left;
  glm::vec3 direction_left_vec3(direction_left);
  glm::vec3 fov_left = fov_center + direction_left_vec3 * (width_ / 2.0f);
  glm::vec3 fov_right = fov_center + direction_left_vec3 * (width_ / -2.0f);

  // Test transformations
  // TODO: remove
  std::cout << "FoV: \n"
      << "Matrix: (" << "\n" 
      << matrix_rotate_left[0][0] << ", " << matrix_rotate_left[0][1] << ", " << matrix_rotate_left[0][2] << ", " << matrix_rotate_left[0][2] <<"\n"
      << matrix_rotate_left[1][0] << ", " << matrix_rotate_left[1][1] << ", " << matrix_rotate_left[1][2] << ", " << matrix_rotate_left[1][2] <<"\n"
      << matrix_rotate_left[2][0] << ", " << matrix_rotate_left[2][1] << ", " << matrix_rotate_left[2][2] << ", " << matrix_rotate_left[2][2] <<"\n"
      << matrix_rotate_left[3][0] << ", " << matrix_rotate_left[3][1] << ", " << matrix_rotate_left[3][2] << ", " << matrix_rotate_left[3][2] <<")\n"
      << "Center: (" << fov_center[0] << ", " << fov_center[1] << ", " << fov_center[2] <<")\n"
      << "Left: (" << fov_left[0] << ", " << fov_left[1] << ", " << fov_left[2] <<")\n"
      << "Right: (" << fov_right[0] << ", " << fov_right[1] << ", " << fov_right[2] <<")\n"
      << std::endl;
  

  glm::mat4 matrix_rotate_up = glm::rotate(90.0f, normalized_direction);

  glm::vec4 direction_up = direction_left * matrix_rotate_up;
  glm::vec3 direction_up_vec3(direction_up);
  glm::vec3 fov_min = fov_left + direction_up_vec3 * (height_ / 2.0f);
  glm::vec3 fov_max = fov_right + direction_up_vec3 * (height_ / -2.0f);

  std::cout << "FoV: \n"
	  << "Min: (" << fov_min[0] << ", " << fov_min[1] << ", " << fov_min[2] << ")\n"
	  << "Max: (" << fov_max[0] << ", " << fov_max[1] << ", " << fov_max[2] << ")\n"
	  << std::endl;

  FoV f{fov_min, fov_max};
  return f;
}


Ray Renderer::compute_camera_ray(Pixel const& p) const {

  glm::vec3 direction = {0.0f, 0.0f, -1.0f * camera_.direction[2]};

  Ray r{ camera_.position, glm::normalize(direction)};
  return r;
};

Color Renderer::trace(Ray const& r) const {

  // TO BE IMPLEMENTED
  return Color{(std::rand() % 100) / 100.0f, (std::rand() % 100) / 100.0f, (std::rand() % 100) / 100.0f};
};
