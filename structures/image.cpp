#include <math.h>
#include <stdlib.h>
#include <vector>

using namespace std;

class CellImage {
  public:
    CellImage(std::size_t width, std::size_t height, const rgb_color& color)
      : width_(width), height_(height)
    {
      pixels_ = new rgb_color[width_ * height_];
      std::fill_n(pixels_, width_ * height_, color);
    }
    std::size_t width() const { return width_; }
    std::size_t height() const { return height_; }
    const rgb_color& operator()(std::size_t row, std::size_t col) const
    {
      return pixels_[(row * width_) + col];
    }
    rgb_color& operator()(std::size_t row, std::size_t col)
    {
      return pixels_[(row * width_) + col];
    }
    bool write_ppm(std::ostream& os) const;
};
