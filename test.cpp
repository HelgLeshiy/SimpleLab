#include "Parser.h"
#include "Namescope.h"
#include <cmath>

// Sin test function for a global namescope
inline double f_sin(const std::vector<std::shared_ptr<Value>>& args)
{
	// Get the value with double type. (Cast from interface to delivered class TypedValue<double>)
	auto parg = dynamic_cast<TypedValue<double>*>(args[0].get());
	if(!parg)
		throw std::runtime_error("argument type mismatch in function sin");

	// Calculating
	return sin(parg->value);
}

// Other test function
inline double f_print(const std::vector<std::shared_ptr<Value>>& args)
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

int main()
{
	// Global scope
	Namescope *global = new Namescope();

	// Install variables
	global->installVar(std::make_shared< TypedValue<double> >(3.14), "pi");

	// Install functions
	global->installFunction(f_sin, 1, "sin");
	global->installFunction(f_print, 1, "print");

	Parser parser;
	std::string input;

	try
	{
		// Parsing lines until exit
		while(std::getline(std::cin, input), input != "exit")
		{
			std::cout << parser.parse(input, global) << std::endl;
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