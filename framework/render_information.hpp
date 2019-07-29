#ifndef RENDER_INFORMATION_HPP
#define RENDER_INFORMATION_HPP

#include <string>
#include "camera.hpp"

struct RenderInformation
{
    Camera& camera;
    std::string filename = "image.ppm";
    unsigned width = 100;
    unsigned height = 100;
};

#endif //#define RENDER_INFORMATION_HPP