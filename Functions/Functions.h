#pragma once
#include "../Parser/Namescope.h"
#include<string>
#include<vector>
#include<stdexcept>
Matrix f_sin(Namescope*, const std::vector<std::shared_ptr<Value>>&);
Matrix f_cos(Namescope*, const std::vector<std::shared_ptr<Value>>&);
Matrix f_tan(Namescope*, const std::vector<std::shared_ptr<Value>>&);
Matrix f_ctan(Namescope*, const std::vector<std::shared_ptr<Value>>&);
Matrix f_sinh(Namescope*, const std::vector<std::shared_ptr<Value>>&);
Matrix f_cosh(Namescope*, const std::vector<std::shared_ptr<Value>>&);
Matrix f_tanh(Namescope*, const std::vector<std::shared_ptr<Value>>&);
Matrix f_ctanh(Namescope*, const std::vector<std::shared_ptr<Value>>&);
Matrix f_lengthStr(Namescope*, const std::vector<std::shared_ptr<Value>>&);
Matrix f_random(Namescope*, const std::vector<std::shared_ptr<Value>>&);