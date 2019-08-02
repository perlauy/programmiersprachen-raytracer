#include "box.hpp"


Box::Box() :
  Shape(),
  minimum_{0.f,0.f,0.f},
  maximum_{1.f,1.f,1.f}
{}

Box::Box(std::string const& name, std::shared_ptr<Material> const& material, glm::vec3 const& minimum, glm::vec3 const& maximum) : 
  Shape(name, material),
  minimum_{minimum},
  maximum_{maximum}
{}


float Box::area() const {
  return (
    (maximum_[0] - minimum_[0]) * (maximum_[1] - minimum_[1])
    + (maximum_[0] - minimum_[0]) * (maximum_[2] - minimum_[2])
    + (maximum_[1] - minimum_[1]) * (maximum_[2] - minimum_[2])
    ) * 2;
}

float Box::volume() const {
  return (maximum_[0] - minimum_[0]) * (maximum_[1] - minimum_[1]) * (maximum_[2] - minimum_[2]);
}

HitPoint Box::intersect(Ray const& ray) const {
  Ray trans_ray = transform_ray(Shape::world_transformation_inv_, ray);
  glm::vec3 central = minimum_ + (1.0f/2.0f) * (maximum_ - minimum_); 
  glm::vec3 origin_to_central = central - ray.origin;
  HitPoint result{};
  for (int index = 0; index < 3; ++index) {
	  if (ray.origin[index] > maximum_[index]
		  || (ray.origin[index] > minimum_[index] && ray.direction[index] > 0)) {
		  hit_test(result, trans_ray, maximum_[index], index);
	  }
	  else {
		  hit_test(result, trans_ray, minimum_[index], index);
	  };
  };
  return result;
}

// HitPoint Box::intersect(Ray const& ray) const {
//   Ray trans_ray = transform_ray(Shape::world_transformation_, ray);
//   HitPoint result{};
//   for (int i = 0; i < 6; ++i) {
//     HitPoint dummy{};
//     bool test;
//     if ( i  < 3) {
//       test = hit_test(dummy, trans_ray, minimum_[i % 3], i % 3);
//     } else {
//       test = hit_test(dummy, trans_ray, maximum_[i % 3], i % 3);
//     }
//     if (test && result.t > dummy.t) {result = dummy;
//       //std::cout << "h";
//     }
//   }
//   return result;
// }

bool Box::hit_test(HitPoint& result, Ray& ray, float fixed_value, int index) const {
  glm::vec3 normalized_direction = glm::normalize(ray.direction);

  if (ray.direction[index] != 0) {
    // calculates t for bringing the resulting point to fixed value in index index
    float distance = (fixed_value - ray.origin[index]) / normalized_direction[index];
    // calculates the resulting point
    glm::vec3 resulting_point = ray.origin + normalized_direction * distance;

    // Comparison having problems with float appreciation. Approx?
    // the denugger shows 2.0000048 > 2.000000...

    float epsilon = 0.01;
    if ((minimum_[(index + 1) % 3] - epsilon <= resulting_point[(index + 1) % 3]) 
      && (resulting_point[(index + 1) % 3] <= maximum_[(index + 1) % 3] + epsilon)
      && (minimum_[(index + 2) % 3] - epsilon <= resulting_point[(index + 2) % 3])
      && (resulting_point[(index + 2) % 3] <= maximum_[(index + 2) % 3] + epsilon)) {

      if (abs(distance) < abs(result.t)) {
 
        result = HitPoint{
          true,
          distance,
          name_,
          material_,
          transform_point(Shape::world_transformation_, resulting_point),
          transform_point(Shape::world_transformation_, normalized_direction)
        };
        return true;
      }
    }
  }
  return false;
}

glm::vec3 Box::get_normal(glm::vec3 const& point) const {
  glm::vec3 trans_point = transform_point(Shape::world_transformation_inv_, point);
  glm::vec3 result{};
  float epsilon = 0.01;
  if ((trans_point[0] <= minimum_[0] + epsilon) && (point[0] >= minimum_[0] - epsilon)) {
    result = {-1.0f,0.0f,0.0f};
    std::cout << "0" << std::endl;
  } else if ((trans_point[0] <= maximum_[0] + epsilon) && (point[0] >= maximum_[0] - epsilon)) {
    result = {1.0f,0.0f,0.0f};
    std::cout << "1" << std::endl;
  } else if ((trans_point[1] <= minimum_[1] + epsilon) &&  (point[1] >= minimum_[1] - epsilon)) {
    result = {0.0f,-1.0f,0.0f};
    std::cout << "2" << std::endl;
  } else if ((trans_point[1] <= maximum_[1] + epsilon) && (point[1] >= maximum_[1] - epsilon)) {
    result = {0.0f,1.0f,0.0f};
    std::cout << "3" << std::endl;
  } else if ((trans_point[2] <= minimum_[2] + epsilon) && (point[2] >= minimum_[2] - epsilon)) {
    result = {0.0f,0.0f,-1.0f};
    //std::cout << "4" << std::endl;
  } else if ((trans_point[2] <= maximum_[2] + epsilon) && (point[2] >= maximum_[2] - epsilon)) {
    result = {0.0f,0.0f,1.0f};
    //std::cout << "5" << std::endl;
  };
  result = glm::normalize(transform_point(Shape::world_transformation_, result));
  std::cout << "[ " << result[0] << ", " << result[1] << ", " << result[2]  << " ]" << std::endl;
  return result;
}

std::ostream& Box::print(std::ostream& os) const {
  Shape::print(os);
  os << "Type: Box\n";
  os << "Minimum: (" << minimum_[0] << ", " << minimum_[1] << ", " << minimum_[2] << ")\tMaximum: (" << maximum_[0] << ", " << maximum_[1] << ", " << maximum_[2] << ")\n";
  if (material_ != nullptr) os << "Material: " << material_->name;
  return os;
}
