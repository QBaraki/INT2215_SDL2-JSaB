#include "vec2d.h"

Vec2d::Vec2d() {
  x = y = 0.0f;
}

Vec2d::Vec2d(double x_, double y_) {
  x = x_;
  y = y_;
}

Vec2d Vec2d::operator+(const Vec2d& other) {
  return Vec2d(x + other.x, y + other.y);
}

Vec2d& Vec2d::operator+=(const Vec2d& other) {
  x += other.x;
  y += other.y;
  return *this;
}

Vec2d Vec2d::operator-(const Vec2d& other) {
  return Vec2d(x - other.x, y - other.y);
}

Vec2d& Vec2d::operator-=(const Vec2d& other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

Vec2d Vec2d::operator*(const double& other) {
  return Vec2d(x * other, y * other);
}

Vec2d& Vec2d::operator*=(const Vec2d& other) {
  x *= other.x;
  y *= other.y;
  return *this;
}

Vec2d& Vec2d::operator*=(const double& other) {
  x *= other;
  y *= other;
  return *this;
}

Vec2d& Vec2d::operator/=(const double& other) {
  x /= other;
  y /= other;
  return *this;
}