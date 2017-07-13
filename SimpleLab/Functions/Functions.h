#pragma once
#include "../Parser/Namescope.h"
#include <string>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <stdexcept>

Value* f_sin(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_cos(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_tan(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_ctan(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_sinh(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_cosh(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_tanh(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_ctanh(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_logn(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_log(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_lengthStr(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_random(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_integral(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_differencial(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_minFunc(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_maxFunc(app *appPtr, Namescope*, const std::vector<Value*>&);

Value* f_arcsin(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_arccos(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_arctan(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_arcctan(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_arcsinh(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_arccosh(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_arctanh(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_arcctanh(app *appPtr, Namescope*, const std::vector<Value*>&);

Value* f_backlogn(app *appPtr, Namescope*, const std::vector<Value*>&);
Value* f_backlog(app *appPtr, Namescope*, const std::vector<Value*>&);
