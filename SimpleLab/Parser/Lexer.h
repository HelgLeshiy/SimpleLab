#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <cctype>
#include <map>
#include <sstream>
#include <functional>
#include <conio.h>

const std::string OPERATORS = ",+-*/=<>!";
enum SymType
{
	IDENT,
	NUMBER,
	STRING,
	OPERATOR,
	LBR = ')',
	RBR = '('
};

struct Token
{
	SymType sym;
	std::string value;

	Token& operator= (const Token& other) { sym = other.sym; value = other.value; return *this; }
};

class Lexer
{
public:
	void startScan(const std::string& input);
	Token scan();

private:
	void getChar();
	void skipWhite();
	void skipComma();
	void match(char c);
	std::string getName();
	std::string getNum();
	std::string getOp();
	std::string getString();

	bool iswhite(char c) { return c == ' '; }
	bool isOp(char c) { return OPERATORS.find(c) != std::string::npos; }

private:
	void init();
	char look;

	std::stringstream ss;
};