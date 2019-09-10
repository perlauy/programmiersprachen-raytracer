// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

// Project files
#include "camera.hpp"
#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "ray.hpp"
#include "scene.hpp"

// External libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/ulp.hpp>
#include <glm/gtx/vector_angle.hpp>


// Standard libraries
#include <cmath>
#include <string>
#include <array>
#include <memory>


class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file, Scene const& s, std::shared_ptr<Camera> const& c);

  void render();
  void render(bool anti_alias);
  void write(Pixel const& p);

  inline std::vector<Color> const& color_buffer() const
  {
	  return color_buffer_;
  };

private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;

  Scene scene_;
  std::shared_ptr<Camera> camera_;

  Ray compute_camera_ray(Pixel const& p) const;
  std::vector<Ray> compute_camera_rays(Pixel const& p, float deviation) const;
  Color trace(Ray const& r, float priority) const;
  glm::mat4 get_camera_matrix() const;
  Color shade(std::shared_ptr<Shape> const& s, HitPoint const& hp, float priority) const;

};

#endif // #ifndef BUW_RENDERER_HPP
