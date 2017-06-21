#pragma once
#include "../Parser/Namescope.h"
#include<string>
#include<math.h>
#include<vector>
#include <cstdlib>
#include<stdexcept>

double f_sin		(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_cos		(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_tan		(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_ctan		(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_sinh		(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_cosh		(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_tanh		(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_ctanh		(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_logn		(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_log		(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_lengthStr	(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_random		(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_integral	(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_differencial(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_minFunc	(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_maxFunc	(Namescope*, const std::vector<std::shared_ptr<Value>>&);

double f_arcsin		(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_arccos		(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_arctan		(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_arcctan	(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_arcsinh	(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_arccosh	(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_arctanh	(Namescope*, const std::vector<std::shared_ptr<Value>>&);
double f_arcctanh	(Namescope*, const std::vector<std::shared_ptr<Value>>&);

double f_backlogn	(Namescope*, const std::vector<std::shared_ptr<Value>>&);
