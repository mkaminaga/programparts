//
// @file main.cc
// @brief Test of sort of indices.
// @author Mamoru Kaminaga
// @date 2019-11-03 10:38:13
// Copyright 2019 Mamoru Kaminaga
//
#include <stdint.h>
#include <stdio.h>
#include <cmath>
#include <vector>

constexpr double PI = 3.14159265;

inline double radians_to_degrees(double radians) {
  return (180.0 / PI) * radians;
}

inline double degrees_to_radians(double degrees) {
  return (PI / 180.0) * degrees;
}

double round_degrees(double degrees) {
  if (degrees < 0) {
    degrees += 360 * std::ceil(std::fabs(degrees) / 360.0);
  } else {
    degrees -= 360 * std::floor(std::fabs(degrees) / 360.0);
  }
  return degrees;
}

double round_radians(double radians) {
  if (radians < 0) {
    radians += (2 * PI) * std::ceil(std::fabs(radians) / (2 * PI));
  } else {
    radians -= (2 * PI) * std::floor(std::fabs(radians) / (2 * PI));
  }
  return radians;
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  std::vector<double> data = {30, -30, 370, -370, 730, -730};
  for (auto& it : data) {
    printf("deg: %f (%f)-> %f (%f)\n", it, degrees_to_radians(it),
           round_degrees(it), degrees_to_radians(round_degrees(it)));
    printf("rad: %f (%f)-> %f (%f)\n", degrees_to_radians(it),
           radians_to_degrees(degrees_to_radians(it)),
           round_radians(degrees_to_radians(it)),
           radians_to_degrees(round_radians(degrees_to_radians(it))));
    printf("\n");
  }

  return 0;
}
