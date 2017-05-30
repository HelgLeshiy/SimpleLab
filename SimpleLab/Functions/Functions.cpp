#include "Functions.h"
#include "../Parser/Parser.h"
using namespace std;

double f_sin(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<double>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function sin");
	return sin(arg1->value);
}

double f_cos(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<double>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function cos");
	return cos(arg1->value);
}

double f_tan(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<double>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function tg");
	return tan(arg1->value);
}

double f_ctan(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<double>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function ctg");
	return 1/tan(arg1->value);
}

double f_sinh(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<double>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function sinh");
	return sinh(arg1->value);
}

double f_cosh(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<double>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function cosh");
	return cosh(arg1->value);
}

double f_tanh(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<double>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function tanh");
	return tanh(arg1->value);
}

double f_ctanh(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<double>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function ctanh");
	return 1/tanh(arg1->value);
}

double f_logn(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<double>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function logn");
	return log(arg1->value);
}

double f_log(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<double>*)args[0].get();
	auto arg2 = (TypedValue<double>*)args[1].get();
	if(!arg1 || !arg2)
		throw std::runtime_error("argument type mismatch in function log");
	return log(arg1->value)/log(arg2->value);
}

double f_lengthStr(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<string>*)args[0].get();
	if(!arg1)
		throw std::runtime_error("argument type mismatch in function length");
	return arg1->value.length();
}

double f_random(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<double>*)args[0].get();
	auto arg2 = (TypedValue<double>*)args[1].get();
	if(!arg1 || !arg2)
		throw std::runtime_error("argument type mismatch in function random");
	return rand()%(int)(arg2->value-arg1->value)+arg1->value;
}

double f_integral(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<std::string>*)args[0].get();
	auto arg2 = (TypedValue<double>*)args[1].get();
	auto arg3 = (TypedValue<double>*)args[2].get();
	if(!arg1 || !arg2 || !arg3)
		throw std::runtime_error("argument type mismatch in function integral");
	int n = 2;
	double h = (arg3->value - arg2->value)/n;
	Parser p;
	Namescope localScope(Na);
	localScope.setVar(std::make_shared< TypedValue<double> >(arg2->value), "x");
	double fLow = p.parse(arg1->value, &localScope);
	localScope.setVar(std::make_shared< TypedValue<double> >((arg2->value+arg3->value)/2), "x");
	double fMid = p.parse(arg1->value, &localScope);
	localScope.setVar(std::make_shared< TypedValue<double> >(arg3->value), "x");
	double fHigh = p.parse(arg1->value, &localScope);
	double S = (fLow + 4*fMid + fHigh)*(h/3);
	double S1;
	do
	{
		n *= 2;
		h = (arg3->value-arg2->value)/n;
		S1 = S;
		int c = 4;
		double x = arg2->value;
		S = fLow+fHigh;
		for(int o = 1; o <= n-1; o++)
		{
			x += h;
			localScope.setVar(std::make_shared< TypedValue<double> >(x), "x");
			double fX = p.parse(arg1->value, &localScope);
			S += c*fX;
			c = 6-c;
		}	
		S *= h/3;
	}while(fabs(S-S1)/15 >= 0.00000001);
	return S;
}
/*
double f_differencial(Namescope* Na, const vector<shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<std::string>*)args[0].get();
	auto arg2 = (TypedValue<double>*)args[1].get();
	auto arg3 = (TypedValue<double>*)args[2].get();
	auto arg4 = (TypedValue<double>*)args[3].get();
	auto arg5 = (TypedValue<double>*)args[4].get();
	if(!arg1 || !arg2 || !arg3 || !arg4 || !arg5)
		throw std::runtime_error("argument type mismatch in function differencial");
	int n = (arg5->value-arg2->value)/arg4->value + 1;
	Parser p;
	Namescope localScope(Na);
	for(int k = 1; k <= n; k++)
	{
		double h = arg4->value;
		int m = 1;

		localScope.setVar(std::make_shared< TypedValue<double> >(arg2->value), "x");
		localScope.setVar(std::make_shared< TypedValue<double> >(arg3->value), "y");
		double k1 = p.parse(arg1->value, &localScope);
	
		localScope.setVar(std::make_shared< TypedValue<double> >(arg2->value+h/2), "x");
		localScope.setVar(std::make_shared< TypedValue<double> >(arg3->value+h*k1/2), "y");
		double k2 = p.parse(arg1->value, &localScope);
	
		localScope.setVar(std::make_shared< TypedValue<double> >(arg2->value+h/2), "x");
		localScope.setVar(std::make_shared< TypedValue<double> >(arg3->value+h*k2/2), "y");
		double k3 = p.parse(arg1->value, &localScope);

		localScope.setVar(std::make_shared< TypedValue<double> >(arg2->value+h), "x");
		localScope.setVar(std::make_shared< TypedValue<double> >(arg3->value+h*k3), "y");
		double k4 = p.parse(arg1->value, &localScope);
		
		double y = arg3->value+(h/6)*(k1+2*k2+2*k3+k4);
		do
		{
			double y1 = y;
			h /= 2;
			double x = arg2->value;
			y = arg3->value;
			m *= 2;
			for(int j = 1; j <= m; j++)
			{
				y = y1;
				localScope.setVar(std::make_shared< TypedValue<double> >(x), "x");
				localScope.setVar(std::make_shared< TypedValue<double> >(y), "y");
				k1 = p.parse(arg1->value, &localScope);

				localScope.setVar(std::make_shared< TypedValue<double> >(x+h/2), "x");
				localScope.setVar(std::make_shared< TypedValue<double> >(y+h*k1/2), "y");
				k2 = p.parse(arg1->value, &localScope);

				localScope.setVar(std::make_shared< TypedValue<double> >(x+h/2), "x");
				localScope.setVar(std::make_shared< TypedValue<double> >(y+h*k2/2), "y");
				k3 = p.parse(arg1->value, &localScope);

				localScope.setVar(std::make_shared< TypedValue<double> >(x+h), "x");
				localScope.setVar(std::make_shared< TypedValue<double> >(y+h*k3), "y");
				k4 = p.parse(arg1->value, &localScope);

				y1 = y+(h/6)*(k1+2*k2+2*k3+k4);
				x += h;
			}
		}while(fabs(y-y1) >= 0.00000001);
		arg2->value += arg4->value;
		arg3->value = y;
	}
	return 
}
*/
double f_minFunc(Namescope* Na, const vector <shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<std::string>*)args[0].get();
	auto arg2 = (TypedValue<double>*)args[1].get();
	auto arg3 = (TypedValue<double>*)args[2].get();
	if(!arg1 || !arg2 || !arg3)
		throw std::runtime_error("argument type mismatch in function minimum of function");	
	double k1 = (3-sqrt(5))/2;
	double k2 = 1-k1;
	double x1 = arg2->value+k1*(arg3->value-arg2->value);
	double x2 = arg2->value+k2*(arg3->value-arg2->value);
	Parser p;
	Namescope localScope(Na);
	localScope.setVar(std::make_shared< TypedValue<double> >(x1), "x");
	double f1 = p.parse(arg1->value, &localScope);
	localScope.setVar(std::make_shared< TypedValue<double> >(x2), "x");
	double f2 = p.parse(arg1->value, &localScope);
	while(arg3->value-arg2->value >= 0.00000001)
	{
		if(f1<f2)
		{
			arg3->value = x2;
			x2 = x1;
			x1 = arg2->value+k1*(arg3->value-arg2->value);
			f2 = f1;
			localScope.setVar(std::make_shared< TypedValue<double> >(x1), "x");
			f1 = p.parse(arg1->value, &localScope);
		}
		else
		{
			arg2->value = x1;
			x1 = x2;
			x2 = arg2->value+k2*(arg3->value-arg2->value);
			f1 = f2;
			localScope.setVar(std::make_shared< TypedValue<double> >(x2), "x");
			f2 = p.parse(arg1->value, &localScope);
		}
	}
	double x = (arg2->value+arg3->value)/2;
	localScope.setVar(std::make_shared< TypedValue<double> >(x), "x");
	double f = p.parse(arg1->value, &localScope);
	return f;
}

double f_maxFunc(Namescope* Na, const vector <shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<std::string>*)args[0].get();
	auto arg2 = (TypedValue<double>*)args[1].get();
	auto arg3 = (TypedValue<double>*)args[2].get();
	if (!arg1 || !arg2 || !arg3)
		throw std::runtime_error("argument type mismatch in function maximum of function");
	double k1 = (3 - sqrt(5)) / 2;
	double k2 = 1 - k1;
	double x1 = arg2->value + k1*(arg3->value - arg2->value);
	double x2 = arg2->value + k2*(arg3->value - arg2->value);
	Parser p;
	Namescope localScope(Na);
	localScope.setVar(std::make_shared< TypedValue<double> >(x1), "x");
	double f1 = p.parse(arg1->value, &localScope);
	localScope.setVar(std::make_shared< TypedValue<double> >(x2), "x");
	double f2 = p.parse(arg1->value, &localScope);
	while (arg3->value - arg2->value >= 0.00000001)
	{
		if (f1<f2)
		{
			arg2->value = x1;
			x1 = x2;
			x2 = arg2->value + k2*(arg3->value - arg2->value);
			f1 = f2;
			localScope.setVar(std::make_shared< TypedValue<double> >(x2), "x");
			f2 = p.parse(arg1->value, &localScope);
		}
		else
		{
			arg3->value = x2;
			x2 = x1;
			x1 = arg2->value + k1*(arg3->value - arg2->value);
			f2 = f1;
			localScope.setVar(std::make_shared< TypedValue<double> >(x1), "x");
			f1 = p.parse(arg1->value, &localScope);
		}
	}
	double x = (arg2->value + arg3->value) / 2;
	localScope.setVar(std::make_shared< TypedValue<double> >(x), "x");
	double f = p.parse(arg1->value, &localScope);
	return f;
}