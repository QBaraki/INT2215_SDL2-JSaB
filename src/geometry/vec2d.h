#ifndef VEC2D_H
#define VEC2D_H

class Vec2d {
 public:
  double x, y;

  Vec2d();
  Vec2d(double x_, double y_);

  Vec2d operator+(const Vec2d& other);
  Vec2d& operator+=(const Vec2d& other);
  Vec2d operator-(const Vec2d& other);
  Vec2d& operator-=(const Vec2d& other);
  Vec2d operator*(const double& other);
  Vec2d& operator*=(const Vec2d& other);
  Vec2d& operator*=(const double& other);
  Vec2d& operator/=(const double& other);
};

#endif  // !VEC2D_H