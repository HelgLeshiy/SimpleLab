#include "Functions.h"
using namespace std;

Matrix f_sin(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<Matrix>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function sin");
	return sin(arg1->value);
}

Matrix f_cos(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<Matrix>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function cos");
	return cos(arg1->value);
}

Matrix f_tan(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<Matrix>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function tg");
	return tan(arg1->value);
}

Matrix f_ctan(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<Matrix>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function ctg");
	return ctan(arg1->value);
}

Matrix f_sinh(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<Matrix>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function sinh");
	return sinh(arg1->value);
}

Matrix f_cosh(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<Matrix>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function cosh");
	return cosh(arg1->value);
}

Matrix f_tanh(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<Matrix>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function tanh");
	return tanh(arg1->value);
}

Matrix f_ctanh(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<Matrix>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function ctanh");
	return ctanh(arg1->value);
}

Matrix f_lengthStr(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<string>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function length");
	return arg1->value.length();
}

Matrix f_random(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<Matrix>*)args[0].get();
	auto arg2 = (TypedValue<Matrix>*)args[1].get();
	if(!arg1 || !arg2)
		throw std::runtime_error("argument type mismatch in function random");
	return rand()%(arg2-arg1)+arg1;
}


/*Matrix f_integral(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	string* arg1 = (TypedValue<string>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function integral");
	Matrix* arg2 = (TypedValue<Matrix>*)args[1].get();
	if(!arg2)
		throw std::runtime_error("argument type mismatch in function integral");
	Matrix* arg3 = (TypedValue<string>*)args[2].get();
	if(!arg3)
		throw std::runtime_error("argument type mismatch in function integral");

	Parser pars;
	Na.installVar(new TypedValue<Matrix>(arg2->Value), "x");
	Matrix integ1 = pars.parse(arg1,Na);
	Na.installVar(new TypedValue<Matrix>(arg3->Value), "x");
	Matrix integ2 = pars.parse(arg1,Na);
	return ;
}*/