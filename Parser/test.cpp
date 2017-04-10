#include "Parser.h"
#include "Namescope.h"
#include <cmath>

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

	// All functions in Simple Lab architecture must return a double value!!!
	return p.parse(parg->value, ns);
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

int main()
{
	// Global scope
	Namescope *global = new Namescope();

	// Install variables
	global->installVar(std::make_shared< TypedValue<double> >(3.14), "pi");

	// Install functions
	global->installFunction(f_sin, 1, "sin");
	global->installFunction(f_print, 1, "print");
	global->installFunction(f_parse, 1, "parse");
	global->installFunction(f_rand, 2, "rand");

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
	}

	delete global;

	_getch();
	return 0;
}