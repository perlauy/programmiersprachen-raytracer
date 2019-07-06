# Ray-Tracing


Scene {
  - Container of objects 
  - Container (?) of point light sources
  - Ambient light

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
    intersect() 
}

Sphere : Object {
  
}
Box : Object {
  
}
Tringle (?) : Object {
}
