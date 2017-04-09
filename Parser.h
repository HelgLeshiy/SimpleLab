#pragma once

#include "Namescope.h"
#include "Lexer.h"

class Parser
{
public:
	double parse(const std::string& input, Namescope *scope);

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
	std::stringstream ss;

	Namescope *ns;
	Lexer lexer;
};