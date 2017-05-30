#include "Parser.h"
#include "Namescope.h"
#include <cmath>
#include <memory>
#include "../Functions/Functions.h"

/*
// Sin test function for a global namescope
inline double f_sin(Namescope*, const std::vector<std::shared_ptr<Value>>& args)
{
	// Get the value with double type. (Cast from interface to delivered class TypedValue<double>)
	auto parg = dynamic_cast<TypedValue<double>*>(args[0].get());
	if(!parg)
		throw std::runtime_error("argument type mismatch in function sin");

	// Calculating
	return sin(parg->value);
}

// Other test function
inline double f_print(Namescope*, const std::vector<std::shared_ptr<Value>>& args)
{
	// Get the value with string type
	auto parg = dynamic_cast<TypedValue<std::string>*>(args[0].get());
	if(!parg)
		throw std::runtime_error("argument type mismatch in function print");

	// Different things...
	std::cout << parg->value << std::endl;

	// All functions in Simple Lab architecture must return a double value!!!
	return 0;
}

// Other test function
inline double f_parse(Namescope* ns, const std::vector<std::shared_ptr<Value>>& args)
{
	// Get the value with string type
	auto parg = dynamic_cast<TypedValue<std::string>*>(args[0].get());
	if(!parg)
		throw std::runtime_error("argument type mismatch in function print");
	Parser p;
	Namescope local(ns);
	local.setVar(std::make_shared<TypedValue<double>>(10.0), "x");

	// All functions in Simple Lab architecture must return a double value!!!
	return p.parse(parg->value, &local);
}

// Other test function
inline double f_rand(Namescope*, const std::vector<std::shared_ptr<Value>>& args)
{
	// Get the value with string type
	auto parg1 = dynamic_cast<TypedValue<double>*>(args[0].get());
	auto parg2 = dynamic_cast<TypedValue<double>*>(args[1].get());
	if(!parg1 || !parg2)
		throw std::runtime_error("argument type mismatch in function print");

	// All functions in Simple Lab architecture must return a double value!!!
	return (rand()%(static_cast<int>(parg2->value) - static_cast<int>(parg1->value))) + parg1->value;
}
*/

int main(int argc, char **argv)
{
	// Global scope
	Namescope *global = new Namescope();

	// Install variables
	global->setVar(std::make_shared< TypedValue<double> >(3.141592653589793238462643383279), "pi");

	// Install functions
	global->installFunction(f_sin, 1, "sin");
	global->installFunction(f_cos, 1, "cos");
	global->installFunction(f_tan, 1, "tan");
	global->installFunction(f_ctan, 1, "ctan");
	global->installFunction(f_sinh, 1, "sinh");
	global->installFunction(f_cosh, 1, "cosh");
	global->installFunction(f_tanh, 1, "tanh");
	global->installFunction(f_ctanh, 1, "ctanh");
	global->installFunction(f_logn, 1, "logn");
	global->installFunction(f_log, 2, "log");
	global->installFunction(f_lengthStr, 1, "strlen");
	global->installFunction(f_random, 2, "rand");
	global->installFunction(f_integral, 3, "int");
	global->installFunction(f_minFunc, 3, "minF");
	global->installFunction(f_maxFunc, 3, "maxF");

	Parser parser;
	std::string input;

	try
	{
		// Parsing lines until exit
		while(std::getline(std::cin, input), input != "exit")
		{
			double ans = parser.parse(input, global);
			std::cout << '\t' << parser.getLastVar() << " = " << ans << std::endl;
		}
	}
	catch(std::exception& e)
	{
		// Shit happens
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	delete global;

	_getch();
	return 0;
}