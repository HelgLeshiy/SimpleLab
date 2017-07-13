#pragma once
#include <vector>

std::vector<float> operator+(const std::vector<float>& a, const std::vector<float>& b);
std::vector<float> operator-(const std::vector<float>& a, const std::vector<float>& b);
std::vector<float> operator*(const std::vector<float>& a, const std::vector<float>& b);
std::vector<float> operator*(float a, const std::vector<float>& b);
std::vector<float> operator*(const std::vector<float>& a, float b);
std::vector<float> operator/(const std::vector<float>& a, const std::vector<float>& b);
std::vector<float> operator/(const std::vector<float>& a, float b);
float scalar(const std::vector<float>& a, const std::vector<float>& b);