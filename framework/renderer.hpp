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
#include "fov.hpp"
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


// Standard libraries
#include <cmath>
#include <string>


class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file, Scene const& s, Camera const& c);

  void render();
  void write(Pixel const& p);

  inline std::vector<Color> const& color_buffer() const
  {
    return color_buffer_;
  }

private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;

  Scene scene_;
  Camera camera_;

  Ray compute_camera_ray(Pixel const& p) const;
  FoV compute_fov() const;
  Color trace(Ray const& r) const;
};

#endif // #ifndef BUW_RENDERER_HPP
