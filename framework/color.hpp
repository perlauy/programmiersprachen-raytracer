// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Color
// -----------------------------------------------------------------------------

#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>

struct Color
{

  friend std::ostream& operator<<(std::ostream& os, Color const& c)
  {
    os << "(" << c.r << "," << c.g << "," << c.b << ")\n";
    return os;
  }

  Color& operator+=(Color const& other)
  {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
  }

  Color& operator-=(Color const& other)
  {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
  }

  friend Color operator+(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp += b;
    return tmp;
  }

  friend Color operator-(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp -= b;
    return tmp;
  }

  friend Color operator*(Color const& a, float k)
  {
    auto tmp(a);
    tmp.r = tmp.r*k;
    tmp.g = tmp.g*k;
    tmp.b = tmp.b*k;
    return tmp;
  }

  // friend Color rgb_to_hsl(Color const& c) 
  // { 
  //   int max_ind = 0;
  //   if (c.r >= c.b && c.r >= c.g) {
  //     max_ind = 0;
  //   } else if (c.g >= c.r && c.g >= c.b) else {
  //     max_ind = 1;
  //   } else {
  //     max_ind = 2;
  //   }

  //   int min_ind = 0;
  //   if (c.r >= c.b && c.r >= c.g) {
  //     min_ind = 0;
  //   } else if (c.g >= c.r && c.g >= c.b) else {
  //     min_ind = 1;
  //   } else {
  //     min_ind = 2;
  //   }
  //   float h = 0;
  //   if (c[max_ind] != c[min_ind]) {
  //     h = 60 * (2*max_ind + (c[max_ind+1 % 3] - c[max_ind+2 % 3])/(c[max_ind]- c[min_ind]))
  //   }
  // }


  float r;
  float g;
  float b;
};

#endif //#define BUW_COLOR_HPP
