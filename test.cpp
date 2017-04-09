#include "Parser.h"
#include "Namescope.h"
#include <cmath>

inline double f_sin(const std::vector<std::shared_ptr<Value>>& args)
{
	auto parg = dynamic_cast<TypedValue<double>*>(args[0].get());
	if(!parg)
		throw std::runtime_error("argument type mismatch in function sin");

	return sin(parg->value);
}

inline double f_print(const std::vector<std::shared_ptr<Value>>& args)
{
	auto parg = dynamic_cast<TypedValue<std::string>*>(args[0].get());
	if(!parg)
		throw std::runtime_error("argument type mismatch in function print");

	std::cout << parg->value << std::endl;

	return 0;
}

int main()
{
	Namescope *global = new Namescope();

	global->installVar(std::make_shared< TypedValue<double> >(3.14), "pi");

	global->installFunction(f_sin, 1, "sin");
	global->installFunction(f_print, 1, "print");

	Parser parser;
	std::string input;

	try
	{
		while(std::getline(std::cin, input), input != "exit")
		{
			std::cout << parser.parse(input, global) << std::endl;
		}
	}
	catch(std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	delete global;

	_getch();
	return 0;
}