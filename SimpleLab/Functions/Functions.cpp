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

Matrix f_logn(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<Matrix>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function logn");
	return log(arg1->value);
}

Matrix f_log(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<Matrix>*)args[0].get();
	auto arg2 = (TypedValue<Matrix>*)args[1].get();
	if(!arg1 || !arg2)
		throw std::runtime_error("argument type mismatch in function log");
	return log(arg1->value)/log(arg2->value);
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



/*Matrix f_func(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	
}*/

Matrix f_integral(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<Matrix>*)args[0].get();
	auto arg2 = (TypedValue<Matrix>*)args[1].get();
	if(!arg1 || !arg2)
		throw std::runtime_error("argument type mismatch in function integral");
	int n = 2;
	double h = (arg2-arg1)/n;
	double S = (func(arg1) + 4*func((arg1+arg2)/2) + func(arg2))*(h/3);
	do
	{
		n *= 2;
		h = (arg2-arg1)/n;
		double S1 = S;
		int c = 4;
		int x = arg1;
		S = func(arg1)+func(arg2);
		for(int o = 1; o <= n-1; o++)
		{
			x += h;
			S += c*func(x);
			c = 6-c;
		}	
		S *= h/3;
	}while(fabs(S-S1)/15 >= 0.00000001);
	return S;
}

Matrix f_differencial(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<Matrix>*)args[0].get();
	auto arg2 = (TypedValue<Matrix>*)args[1].get();
	auto arg3 = (TypedValue<Matrix>*)args[2].get();
	auto arg4 = (TypedValue<Matrix>*)args[3].get();
	if(!arg1 || !arg2 || !arg3 || !arg4)
		throw std::runtime_error("argument type mismatch in function differencial");
	int n = (arg4-arg1)/arg3 + 1;
	for(int k = 1; k <= n; k++)
	{
		double h = arg3;
		int m = 1;
		
		double k1 = func(arg1,arg2);
		double k2 = func(arg1+h/2, arg2+h*k1/2);
		double k3 = func(arg1+h/2, arg2+h*k2/2);
		double k4 = func(arg1+h, arg2+h*k3);
		double y = arg2+(h/6)*(k1+2*k2+2*k3+k4);
		do
		{
			double y1 = y;
			h /= 2;
			double x = arg1;
			y = arg2;
			m *= 2;
			for(int j = 1; j <= m; j++)
			{
				y = y1;
				double k1 = func(x,y);
				double k2 = func(x+h/2, y+h*k1/2);
				double k3 = func(x+h/2, y+h*k2/2);
				double k4 = func(x+h, y+h*k3);
				y1 = y+(h/6)*(k1+2*k2+2*k3+k4);
				x += h;
			}
		}while(fabs(y-y1) >= 0.00000001);
		arg1 += arg3;
		arg2 = y;
	}
	return 
}

Matrix f_minFunc(Namescope* Na, const<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<Matrix>*)args[0].get();
	auto arg2 = (TypedValue<Matrix>*)args[1].get();
	if(!arg1 || !arg2)
		throw std::runtime_error("argument type mismatch in function minimum of function");	
	double k1 = (3-sqrt(5))/2;
	double k2 = 1-k1;
	double x1 = arg1+k1*(arg2-arg1);
	double x2 = arg1+k2*(arg2-arg1);
	double f1 = func(x1);
	double f2 = func(x2);
	while(arg2-arg1 >= 0.00000001)
	{
		if(f1<f2)
		{
			arg2 = x2;
			x2 = x1;
			x1 = arg1+k1*(arg2-arg1);
			f2 = f1;
			f1 = func(x1);
		}
		else
		{
			arg1 = x1;
			x1 = x2;
			x2 = arg1+k2*(arg2-arg1);
			f1 = f2;
			f2 = func(x2);
		}
	}
	double x = (arg1+arg2)/2;
	double f = func(x);
	return 
}

Matrix f_maxFunc(Namescope* Na, const<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<Matrix>*)args[0].get();
	auto arg2 = (TypedValue<Matrix>*)args[1].get();
	if(!arg1 || !arg2)
		throw std::runtime_error("argument type mismatch in function maximum of function");	
	double k1 = (3-sqrt(5))/2;
	double k2 = 1-k1;
	double x1 = arg1+k1*(arg2-arg1);
	double x2 = arg1+k2*(arg2-arg1);
	double f1 = func(x1);
	double f2 = func(x2);
	while(arg2-arg1 >= 0.00000001)
	{
		if(f1<f2)
		{
			arg1 = x1;
			x1 = x2;
			x2 = arg1+k2*(arg2-arg1);
			f1 = f2;
			f2 = func(x2);
		}
		else
		{
			arg2 = x2;
			x2 = x1;
			x1 = arg1+k1*(arg2-arg1);
			f2 = f1;
			f1 = func(x1);
		}
	}
	double x = (arg1+arg2)/2;
	double f = func(x);
	return 
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