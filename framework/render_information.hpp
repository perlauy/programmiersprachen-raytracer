#ifndef RENDER_INFORMATION_HPP
#define RENDER_INFORMATION_HPP

// Project files
#include "camera.hpp"

// Standard libraries
#include <string>
#include <memory>


struct RenderInformation
{
    std::shared_ptr<Camera> camera;
    std::string filename = "image.ppm";
    unsigned width = 100;
    unsigned height = 100;
};

#endif //#define RENDER_INFORMATION_HPP