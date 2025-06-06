#pragma once
#include <iostream>
#include <utility>

class [[nodiscard]] point {
private:
  int x_{};
  int y_{};

public:
  point() = delete;
  point(int x, int y) : x_{x}, y_{y} {}
  point(point const& p) : x_{p.x_}, y_{p.y_} {}
  point(point&& p) noexcept : x_{std::move(p.x_)}, y_{std::move(p.y_)} {}

  inline int x() const {
    return x_;
  }
  inline int y() const {
    return y_;
  }

  inline void x(int x) {
    x_ = x;
  }
  inline void y(int y) {
    y_ = y;
  }

  inline void x_move(int x) {
    x_ += x - x_;
  }
  inline void y_move(int y) {
    y_ += y - y_;
  }

  void move_to(point p) {
    x_move(p.x());
    y_move(p.y());
  }

  point& operator=(point p) {
    _swap(*this, p);

    return *this;
  }

  friend void _swap(point& a, point& b) {
    std::swap(a.x_, b.x_);
    std::swap(a.y_, b.y_);
  }

  inline int operator-(point const& p) const {
    return std::abs(x_ - p.x_) + std::abs(y_ - p.y_);
  }

  inline bool operator==(point const& rhs) const {
    return x_ == rhs.x_ && y_ == rhs.y_;
  }

  friend std::ostream& operator<<(std::ostream& os, point const& p) {
    return os << p.x_ << ',' << p.y_;
  }

  friend int steps(point& a, point const& b) {
    return a - b;
  }

  ~point() = default;
};