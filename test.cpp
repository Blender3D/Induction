#include <cmath>
#include <iostream>
#include <fstream>
#include <algorithm>

struct Vector {
  float x, y, z;
  
  Vector(float _x = 0.0, float _y = 0.0, float _z = 0.0) {
    x = _x;
    y = _y;
    z = _z;
  }
  
  Vector operator+(const Vector &other) const {
    return Vector(x + other.x, y + other.y, z + other.z);
  }
  
  Vector operator+(float other) const {
    return Vector(x + other, y + other, z + other);
  }
  
  Vector operator-(const Vector &other) const {
    return Vector(x - other.x, y - other.y, z - other.z);
  }
  
  Vector operator*(float other) const {
    return Vector(x * other, y * other, z * other);
  }
  
  Vector operator*(Vector other) const {
    return Vector(x * other.x, y * other.y, z * other.z);
  }
  
  Vector operator/(float other) const {
    return *this * (1.0 / other);
  }
  
  Vector norm() {
    return *this * (1.0 / sqrt(x*x + y*y + z*z));
  }
  
  float dot(Vector other) const {
    return x * other.x + y * other.y + z * other.z;
  }
  
  Vector cross(Vector other) const {
    return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
  }
  
  float abs() {
    return sqrt(x*x + y*y + z*z);
  }
};

struct Ray {
  Vector origin;
  Vector direction;
  
  Ray(Vector _origin, Vector _direction) {
    origin = _origin;
    direction = _direction.norm();
  }
  
  Vector position(float &time) const {
    return origin + direction * time;
  }
};

class quadrilateral
{
public:
  quadrilateral(const Vector& v_00, const Vector& v_10,
    const Vector& v_11, const Vector& v_01)
  {
    vertices[0] = v_00;
    vertices[1] = v_10;
    vertices[2] = v_11;
    vertices[3] = v_01;
  }
  const Vector& v_00() const { return vertices[0]; }
  const Vector& v_10() const { return vertices[1]; }
  const Vector& v_11() const { return vertices[2]; }
  const Vector& v_01() const { return vertices[3]; }
private:
  Vector vertices[4];
};

class image
{
public:
  image(std::size_t width, std::size_t height, const Vector& color)
    : width_(width), height_(height)
  {
    pixels_ = new Vector[width_ * height_];
    std::fill_n(pixels_, width_ * height_, color);
  }
  ~image() { delete [] pixels_; }
  std::size_t width() const { return width_; }
  std::size_t height() const { return height_; }
  const Vector& operatox(std::size_t row, std::size_t col) const
  {
    return pixels_[(row * width_) + col];
  }
  Vector& operatox(std::size_t row, std::size_t col)
  {
    return pixels_[(row * width_) + col];
  }
  bool write_ppm(std::ostream& os) const;
private:
  image(const image&);
  image& operator=(const image&);
  std::size_t width_, height_;
  Vector* pixels_;
};

bool image::write_ppm(std::ostream& os) const
{
  os << "P3\n" << width() << ' ' << height() << '\n' << 255 << '\n';

  for (std::size_t row = 0; row < height(); ++row) {

    for (std::size_t col = 0; col < width(); ++col) {

      const Vector& pixel = (*this)(row, col);
      os << static_cast<int>(pixel.x * 255) << ' '
         << static_cast<int>(pixel.y * 255) << ' '
         << static_cast<int>(pixel.z * 255) << ' ';
    }
    os << '\n';
  }
  return os;
}

bool intersect_quadrilateral_Ray(const quadrilateral& q,
  const Ray& r, float& u, float& v, float& t)
{
  static const float eps = float(10e-6);

  // Rejects Rays that are parallel to Q, and Rays that intersect the plane of
  // Q either on the left of the line V00V01 or on the right of the line V00V10.

  Vector E_01 = q.v_10() - q.v_00();
  Vector E_03 = q.v_01() - q.v_00();
  Vector P = cross(r.direction, E_03);
  float det = E_01.dot(P);
  if (std::abs(det) < eps) return false;
  float inv_det = float(1.0) / det;
  Vector T = r.origin() - q.v_00();
  float alpha = T.dot(P) * inv_det;
  if (alpha < float(0.0)) return false;
  // if (alpha > float(1.0)) return false; // Uncomment if VR is used.
  Vector Q = cross(T, E_01);
  float beta = r.direction.dot(Q) * inv_det;
  if (beta < float(0.0)) return false; 
  // if (beta > float(1.0)) return false; // Uncomment if VR is used.

  if ((alpha + beta) > float(1.0)) {

    // Rejects Rays that intersect the plane of Q either on the
    // left of the line V11V10 or on the right of the line V11V01.

    Vector E_23 = q.v_01() - q.v_11();
    Vector E_21 = q.v_10() - q.v_11();
    Vector P_prime = cross(r.direction, E_21);
    float det_prime = E_23.dot(P_prime);
    if (std::abs(det_prime) < eps) return false;
    float inv_det_prime = float(1.0) / det_prime;
    Vector T_prime = r.origin() - q.v_11();
    float alpha_prime = T_prime.dot(P_prime) * inv_det_prime;
    if (alpha_prime < float(0.0)) return false;
    Vector Q_prime = cross(T_prime, E_23);
    float beta_prime = r.direction.dot(Q_prime) * inv_det_prime;
    if (beta_prime < float(0.0)) return false;
  }

  // Compute the Ray parameter of the intersection Vector, and
  // reject the Ray if it does not hit Q.

  t = E_03.dot(Q) * inv_det;
  if (t < float(0.0)) return false; 

  // Compute the barycentric coordinates of the fourth vertex.
  // These do not depend on the Ray, and can be precomputed
  // and stored with the quadrilateral.  

  float alpha_11, beta_11;
  Vector E_02 = q.v_11() - q.v_00();
  Vector n = cross(E_01, E_03);

  if ((std::abs(n.x) >= std::abs(n.y))
    && (std::abs(n.x) >= std::abs(n.z))) {

    alpha_11 = ((E_02.y * E_03.z) - (E_02.z * E_03.y)) / n.x;
    beta_11  = ((E_01.y * E_02.z) - (E_01.z * E_02.y)) / n.x;
  }
  else if ((std::abs(n.y) >= std::abs(n.x))
    && (std::abs(n.y) >= std::abs(n.z))) {  

    alpha_11 = ((E_02.z * E_03.x) - (E_02.x * E_03.z)) / n.y;
    beta_11  = ((E_01.z * E_02.x) - (E_01.x * E_02.z)) / n.y;
  }
  else {

    alpha_11 = ((E_02.x * E_03.y) - (E_02.y * E_03.x)) / n.z;
    beta_11  = ((E_01.x * E_02.y) - (E_01.y * E_02.x)) / n.z;
  }

  // Compute the bilinear coordinates of the intersection Vector.

  if (std::abs(alpha_11 - float(1.0)) < eps) {    

    // Q is a trapezium.
    u = alpha;
    if (std::abs(beta_11 - float(1.0)) < eps) v = beta; // Q is a parallelogram.
    else v = beta / ((u * (beta_11 - float(1.0))) + float(1.0)); // Q is a trapezium.
  }
  else if (std::abs(beta_11 - float(1.0)) < eps) {

    // Q is a trapezium.
    v = beta;
    u = alpha / ((v * (alpha_11 - float(1.0))) + float(1.0));
  }
  else {

    float A = float(1.0) - beta_11;
    float B = (alpha * (beta_11 - float(1.0)))
      - (beta * (alpha_11 - float(1.0))) - float(1.0);
    float C = alpha;
    float D = (B * B) - (float(4.0) * A * C);
    float Q = float(-0.5) * (B + ((B < float(0.0) ? float(-1.0) : float(1.0))
      * std::sqrt(D)));
    u = Q / A;
    if ((u < float(0.0)) || (u > float(1.0))) u = C / Q;
    v = beta / ((u * (beta_11 - float(1.0))) + float(1.0)); 
  }

  return true;
}

int main()
{
  quadrilateral q(Vector( 0.49421906944, 0.081285633543, 0.100104041766),
                  Vector( 1.00316508089, 0.530985148652, 0.629377264874),
                  Vector( 0.50578093056, 0.918714366457, 0.899895958234),
                  Vector(-0.01235416806, 0.590487788947, 0.484479525901)); 

  image img(256, 256, Vector(0, 0, 0));

  checkerboard_texture texture(4, 4, Vector(1, 0, 0), Vector(1, 1, 1));

  for (std::size_t row = 0; row < img.height(); ++row) {

    float y = (float(img.height() - row - 1) + float(0.5)) / img.height();

    for (std::size_t col = 0; col < img.width(); ++col) {

      float x = (float(col) + float(0.5)) / img.width();
      Ray r(Vector(x, y, 10), Vector(0, 0, -1));

      float u, v, t;
      if (intersect_quadrilateral_Ray(q, r, u, v, t)) {
        img(row, col) = texture(u, v);
      }
    }
  }

  std::ofstream os("image.ppm");
  img.write_ppm(os);

  return 0;
}
