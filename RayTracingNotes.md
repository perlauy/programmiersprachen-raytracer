# Ray-Tracing


struct Scene {
  - Container of objects 
  - Container (?) of point light sources
  - Ambient light
  - Container of materials
}

Camara {
  - Outside scene? Fixed?
  Props:
    Position -> vec3 = origin
    Direction -> vec3 = (0,0,-1)
    Angle -> float
    Resolution -> {width (unsigned int), height (unsigned int)}

  Render()
    Matrix pixels = getPixels(origin, angle, resolution) 
    foreach pixel :
      Ray r{origin, pixel}
      hitPoint closest{} -> Infinite point with background color?

      foreach object in scene :
        hitPoint hp = intersect(r)
        if (hp.hit && hp.distance < closest distance) : closest = hp

      pixel.color = hp.object.shade(Ray r, hp.distance)

}

Object { 
  - Base class for different types (abstract)
  
  Public props & methods:
    Material
    intersect(Ray)
    shade(Ray r, float distance) :
      vec3 point = r.origin + distance * r.direction
      vec3 normal = getNormal(point)
      float intensity
      
      // Should be for each color channel
      foreach point light source :
        vec3 l = normalize(light.origin - point)

        // Diffuse, if light is visible
        intensity += light.intensity * material.diffuse * cos(normal,l)

        // Phong
        vec3 v = normalize(-r)
        vec3 reflection = l - 2 * scalarProduct(l,normal) * normal
        intensity += light.intensity * material.reflection * pow(cos(reflection,v), m)

      intensity += ambient_light.intensity * material.ambient

      return Color{intensity_r, intensity_g, intensity_b}

  private :
    getNormal(Point p) // if p belongs to object, get normal vec
}

Sphere : Object {
  
}
Box : Object {
  
}
Tringle (?) : Object {
}

// ?
Light {
  Color color
}
AmbientLight : Light {
  
}
PointLight : Light {
  vec3 origin
}