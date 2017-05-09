#pragma once

#include "Namescope.h"
#include "Lexer.h"


/**
* Parser class definition.
* Uses for calculating string expressions in a single double value
**/
class Parser
{
public:
	/**
	* Parse (execute) math expression
	* 
	* param input: String with an expression
	* param scope: A namespace with preinstalled functions and variables ( memory )
	*
	* return: result double value
	**/
	double parse(const std::string& input, Namescope *scope);

	const std::string& getLastVar() const { return lastVar; }

private:
	void getToken();
	void skipWhite();
	void match(char c);
	std::string getName();
	double getNum();

	bool isaddop(const std::string& s) { return s == "+" || s == "-"; }
	bool ismulop(const std::string& s) { return s == "*" || s == "/"; }

	double expression();
	double assigment();
	double term();
	double factor();
	double ident();
	void parseParams(std::vector<std::shared_ptr<Value>>& params);

private:
	void init();
	Token curTok;

	//std::map<std::string, double> memory;
	//std::map<std::string, std::function<double(void)>> functions;
	bool hasVarName;
	std::string lastVar;
	std::stringstream ss;

	Namescope *ns;
	Lexer lexer;
};