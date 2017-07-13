#include "Functions.h"
#include "../Parser/Parser.h"
#include "../app.h"
using namespace std;

Value* f_sin(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', sin(((TypedValue<float>*)args[0])->value));
}

Value* f_cos(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', cos(((TypedValue<float>*)args[0])->value));
}

Value* f_tan(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', tan(((TypedValue<float>*)args[0])->value));
}

Value* f_ctan(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', 1/tan(((TypedValue<float>*)args[0])->value));
}

Value* f_sinh(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', sinh(((TypedValue<float>*)args[0])->value));
}

Value* f_cosh(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', cosh(((TypedValue<float>*)args[0])->value));
}

Value* f_tanh(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', tanh(((TypedValue<float>*)args[0])->value));
}

Value* f_ctanh(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', 1/tanh(((TypedValue<float>*)args[0])->value));
}

Value* f_arcsin(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', asin(((TypedValue<float>*)args[0])->value));
}

Value* f_arccos(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', acos(((TypedValue<float>*)args[0])->value));
}

Value* f_arctan(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', atan(((TypedValue<float>*)args[0])->value));
}

Value* f_arcctan(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', 1/atan(((TypedValue<float>*)args[0])->value));
}

Value* f_arcsinh(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', asinh(((TypedValue<float>*)args[0])->value));
}

Value* f_arccosh(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', acosh(((TypedValue<float>*)args[0])->value));
}

Value* f_arctanh(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', atanh(((TypedValue<float>*)args[0])->value));
}

Value* f_arcctanh(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', 1/atanh(((TypedValue<float>*)args[0])->value));
}

Value* f_logn(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', log(((TypedValue<float>*)args[0])->value));
}

Value* f_log(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', log(((TypedValue<float>*)args[0])->value) / log(((TypedValue<float>*)args[1])->value));
}

Value* f_lengthStr(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', ((TypedValue<std::string>*)args[0])->value.length());
}

Value* f_random(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', rand()%(int)(((TypedValue<float>*)args[0])->value - ((TypedValue<float>*)args[1])->value)
									  + ((TypedValue<float>*)args[0])->value);
}

Value* f_integral(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	auto arg1 = (TypedValue<std::string>*)args[0];
	auto arg2 = (TypedValue<float>*)args[1];
	auto arg3 = (TypedValue<float>*)args[2];
	int n = 2;
	double h = (arg3->value - arg2->value)/n;
	Parser p;
	Namescope localScope(ns);
	localScope.setVar(new TypedValue<float>('f', arg2->value), "x");
	Value* fLow = p.parse(appPtr, arg1->value, &localScope);
	localScope.setVar(new TypedValue<float>('f', (arg2->value+arg3->value)/2), "x");
	Value* fMid = p.parse(appPtr, arg1->value, &localScope);
	localScope.setVar(new TypedValue<float>('f', arg3->value), "x");
	Value* fHigh = p.parse(appPtr, arg1->value, &localScope);
	float S = (((TypedValue<float>*)fLow)->value + 4 * ((TypedValue<float>*)fMid)->value + ((TypedValue<float>*)fHigh)->value)*(h/3);
	double S1;
	do
	{
		n *= 2;
		h = (arg3->value-arg2->value)/n;
		S1 = S;
		int c = 4;
		double x = arg2->value;
		S = ((TypedValue<float>*)fLow)->value + ((TypedValue<float>*)fHigh)->value;
		for(int o = 1; o <= n-1; o++)
		{
			x += h;
			localScope.setVar(new TypedValue<float>('f', x), "x");
			Value *fX = p.parse(appPtr, arg1->value, &localScope);
			S += c * ((TypedValue<float>*)fX)->value;
			c = 6-c;
		}	
		S *= h/3;
	}while(fabs(S-S1)/15 >= 0.00000001);
	return new TypedValue<float>('f', S);
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

/*
Value* f_minFunc(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
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

Value* f_maxFunc(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
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
*/

/*double f_equation(Namescope* Na, const vector <shared_ptr<Value>>& args)
{
	auto arg1 = (TypedValue<std::string>*)args[0].get();
	auto arg2 = (TypedValue<double>*)args[1].get();
	auto arg3 = (TypedValue<double>*)args[2].get();
	auto arg4 = (TypedValue<std::string>*)args[3].get();
	if (!arg1 || !arg2 || !arg3 || !arg4)
		throw std::runtime_error("argument type mismatch in function solution of equation");
	Parser p;
	Namescope localScope(Na);
	double x1 = arg2->value;
	double x2 = arg3->value;
	localScope.setVar(std::make_shared< TypedValue<double> >(x1), arg4->value);
	double f1 = p.parse(arg1->value, &localScope);
	localScope.setVar(std::make_shared< TypedValue<double> >(x2), arg4->value);
	double f2 = p.parse(arg1->value, &localScope);
	if (f1 == 0)
		return x1;
	if (f2 == 0)
		return x2;
	while ((f1 > 0 && f2 > 0 || f1 < 0 && f2 < 0) && x2-x1 < 0.00000001)
	{
		double xm = (x1 + x2) / 2;
		localScope.setVar(std::make_shared< TypedValue<double> >(xm), arg4->value);
		double fm = p.parse(arg1->value, &localScope);
		if (fm == 0)
			return xm;

	}
}*/

Value* f_backlogn(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', exp(((TypedValue<float>*)args[0])->value));
}

Value* f_backlog(app *appPtr, Namescope* ns, const std::vector<Value*>& args)
{
	return new TypedValue<float>('f', pow(((TypedValue<float>*)args[0])->value, ((TypedValue<float>*)args[1])->value));
}