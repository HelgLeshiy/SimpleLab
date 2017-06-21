#include "Parser.h"
#include <cmath>

double Parser::parse(const std::string& input, Namescope *scope)
{
	ns = scope;
	if(input.find('=') != std::string::npos)
		hasVarName = true;
	else
		hasVarName = false;

	lexer.startScan(input);
	init();

	return assigment();
}

void Parser::getToken()
{
	curTok = lexer.scan();
}

void Parser::init()
{
	getToken();
}

double Parser::expression()
{
	double ans;

	if(curTok.sym == OPERATOR && curTok.value == "-")
	{
		getToken();
		ans = -term();
	}
	else if(curTok.sym == OPERATOR && curTok.value == "+")
	{
		getToken();
		ans = term();
	}
	else
		ans = term();

	while(curTok.sym == OPERATOR && isaddop(curTok.value))
	{
		if(curTok.value == "+")
		{
			getToken();
			ans += term();
		}
		else if(curTok.value == "-")
		{
			getToken();
			ans -= term();
		}
		else
			throw std::runtime_error("Expected addop");
	}

	return ans;
}

double Parser::assigment()
{
	std::string name;
	if(hasVarName)
	{
		if(curTok.sym != IDENT)
			throw std::runtime_error("Expected identifier");
		name = curTok.value;
		getToken();
		if(curTok.sym != OPERATOR || curTok.value != "=")
			throw std::runtime_error("Expected =");
		getToken();
	}
	else
		name = "ans";

	lastVar = name;

	if(ns->lookupVar(name) != Namescope::LookupResult::found)
	{
		std::shared_ptr<Value> value(std::make_shared< TypedValue<double> >());
		ns->setVar(value, name);
	}

	dynamic_cast<TypedValue<double>*>(ns->getVar(name).get())->value = expression();
		
	return dynamic_cast<TypedValue<double>*>(ns->getVar(name).get())->value;
}

double Parser::term()
{
	double ans = power();
	
	while(curTok.sym == OPERATOR && ismulop(curTok.value))
	{
		if(curTok.value == "*")
		{
			getToken();
			ans *= term();
		}
		else if(curTok.value == "/")
		{
			getToken();
			ans /= term();
		}
		else
			throw std::runtime_error("Expected mulop");
	}

	return ans;
}

double Parser::power()
{
	double ans = factor();

	while (curTok.sym == OPERATOR && curTok.value == "^")
	{
		
		getToken();
		ans = pow(ans, power());
	}

	return ans;
}

double Parser::factor()
{
	double ans;
	if(curTok.sym == LBR)
	{
		getToken();
		ans = expression();
		if(curTok.sym != RBR)
			throw std::runtime_error("Expected )");
		getToken();
	}
	else if(curTok.sym == NUMBER)
	{
		ans = atof(curTok.value.c_str());
		getToken();
	}
	else if(curTok.sym == IDENT)
		ans = ident();
	else
	{
		char msg[64];
		sprintf(msg, "Unexpected lexem %s", curTok.value);
		throw std::runtime_error(msg);
	}

	return ans;
}

void Parser::parseParams(std::vector<std::shared_ptr<Value>>& params)
{
	while(curTok.sym != RBR)
	{
		if(curTok.sym == STRING)
		{
			std::shared_ptr<Value> value(std::make_shared< TypedValue<std::string> >());
			dynamic_cast<TypedValue<std::string>*>(value.get())->value = curTok.value;
			getToken();
			params.push_back(value);
		}
		else
		{
			std::shared_ptr<Value> value(std::make_shared< TypedValue<double> >());
			dynamic_cast<TypedValue<double>*>(value.get())->value = expression();
			params.push_back(value);
		}
	}
}

double Parser::ident()
{
	std::string name = curTok.value;
	getToken();
	if(curTok.sym == LBR)
	{
		getToken();
		std::vector<std::shared_ptr<Value>> params;
		parseParams(params);

		auto lookup = ns->lookupFunc(name, params.size());
		if (lookup == Namescope::LookupResult::not_found)
			throw std::runtime_error("unknown function");
		if (lookup == Namescope::LookupResult::wrong_signature)
			throw std::runtime_error("signature mismatch for function");
		return ns->getFunc(name)->function(ns, params);
	}
	else
	{
		auto lookup = ns->lookupVar(name);
		if (lookup == Namescope::LookupResult::not_found)
			throw std::runtime_error("unknown variable");
		return dynamic_cast<TypedValue<double>*>(ns->getVar(name).get())->value;
	}
}