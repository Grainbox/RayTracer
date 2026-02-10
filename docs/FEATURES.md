# Feature Roadmap

This document describes features planned for the RayTracer that are not yet implemented. Each section provides context, implementation guidance, and references to help contributors get started.

---

## ✅ Hard Shadows

**Priority:** High  
**Difficulty:** Medium  
**Files to modify:** `src/Scene.cpp`

### Description
When calculating lighting for a surface point, cast a **shadow ray** from the intersection point toward each light source. If the shadow ray hits another object before reaching the light, that point is in shadow and should not receive diffuse/specular contribution from that light.

### Implementation Steps
1. After computing `closestInters`, for each light source:
   - Create a ray from `closestInters` toward the light position (offset slightly along the normal to avoid self-intersection: `origin = closestInters + normal * 0.001`)
   - Iterate through all shapes and check if any shape blocks the path (`hits()` returns true with `t < distanceToLight`)
2. If blocked, skip the diffuse and specular contribution for that light
3. Ambient light should still apply (shadows are never fully black)

### References
- [Scratchapixel - Shadows](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/ligths-and-shadows)

---

## ✅ Reflections

**Priority:** Medium  
**Difficulty:** Medium  
**Files to modify:** `src/Scene.cpp`, `includes/shapes/IShape.hpp`

### Description
Reflective surfaces bounce incoming rays. The reflected ray direction is computed as:  
`R = D - 2 * (D · N) * N`  
where `D` is the incoming ray direction and `N` is the surface normal.

### Implementation Steps
1. Add a `reflectivity` property (0.0 to 1.0) to shapes (via `IShape` / `AShape`)
2. Parse `reflectivity` from scene config files
3. In `getColor()`, after computing the surface color:
   - If `reflectivity > 0`, compute the reflected ray direction
   - Recursively call `getColor()` with the reflected ray (add a `depth` parameter, max ~5 bounces)
   - Blend: `finalColor = (1 - reflectivity) * surfaceColor + reflectivity * reflectedColor`

### References
- [Ray Tracing in One Weekend - Metal](https://raytracing.github.io/books/RayTracingInOneWeekend.html#metal)

---

## 🔮 Refractions (Transparency)

**Priority:** Low  
**Difficulty:** Hard  
**Files to modify:** `src/Scene.cpp`, `includes/shapes/IShape.hpp`

### Description
Transparent materials bend light according to **Snell's Law**. Requires tracking whether a ray is entering or exiting a material using the normal direction.

### Implementation Steps
1. Add `transparency` and `refractiveIndex` properties to shapes
2. Implement Snell's Law: `sin(θ₂) = (n₁/n₂) * sin(θ₁)`
3. Handle **total internal reflection** when the angle is too steep
4. Use **Fresnel equations** (or Schlick's approximation) to blend between reflection and refraction
5. Recursively trace the refracted ray (share the `depth` limit with reflections)

### References
- [Scratchapixel - Refraction](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel)

---

## 🔵 Cylinders

**Priority:** Medium  
**Difficulty:** Medium  
**Files to modify:** New file `src/NShapes/Cylinder.cpp`, `includes/shapes/Cylinder.hpp`, `src/NShapes/Factory.cpp`

### Description
Add cylinder primitives (infinite or capped). A cylinder is defined by a center axis, radius, and optional height.

### Implementation Steps
1. Create `Cylinder` class inheriting from `AShape`
2. Ray-cylinder intersection: solve the quadratic equation for the cylinder surface (similar to sphere but in 2D cross-section)
3. For capped cylinders, also test intersection with top/bottom disc caps
4. Normal calculation: for the curved surface, the normal is the vector from the axis to the intersection point (perpendicular to the axis)
5. Register `"cylinders"` in `Factory.cpp`

### References
- [Scratchapixel - Ray-Cylinder Intersection](https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection)

---

## ⚡ Multithreading

**Priority:** High  
**Difficulty:** Easy  
**Files to modify:** `src/Scene.cpp`

### Description
The render loop in `Scene::render()` iterates over pixels sequentially. Since each pixel is independent, this is trivially parallelizable.

### Implementation Steps
1. Replace the outer `for` loop with `std::for_each` + `std::execution::par` (C++17 parallel algorithms), or use `#pragma omp parallel for` (OpenMP)
2. Alternatively, split the image into horizontal bands and assign each band to a `std::thread`
3. Ensure `getColor()` is **thread-safe** (it already is — it only reads shared data)
4. Add `-fopenmp` or link TBB in `CMakeLists.txt` depending on the approach

### Example (OpenMP)
```cpp
#pragma omp parallel for schedule(dynamic)
for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
        Color color = this->getColor(j, i);
        // write to buffer[i * width + j]
    }
}
```

---

## 🔳 Anti-Aliasing (Supersampling)

**Priority:** Low  
**Difficulty:** Easy  
**Files to modify:** `src/Scene.cpp`

### Description
Jagged edges (aliasing) occur because each pixel samples only one ray. **Supersampling** shoots multiple rays per pixel with slight offsets and averages the results.

### Implementation Steps
1. Add a `samples` parameter (e.g., 4 for 2×2 supersampling)
2. In `render()`, for each pixel, shoot `samples` rays with random or grid-based sub-pixel offsets
3. Average the returned colors
4. Higher sample counts = smoother edges but slower rendering

### Example
```cpp
Color finalColor = {0, 0, 0};
int samples = 4;
for (int s = 0; s < samples; s++) {
    double offsetX = (rand() / (double)RAND_MAX) - 0.5;
    double offsetY = (rand() / (double)RAND_MAX) - 0.5;
    Color c = getColor(j + offsetX, i + offsetY);
    finalColor.r += c.r; finalColor.g += c.g; finalColor.b += c.b;
}
finalColor.r /= samples; finalColor.g /= samples; finalColor.b /= samples;
```
