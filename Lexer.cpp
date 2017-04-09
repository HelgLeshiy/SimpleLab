#include "Lexer.h"

void Lexer::startScan(const std::string& input)
{
	ss.clear();
	ss << input << '\n';

	init();
}

Token Lexer::scan()
{
	Token token;
	if(std::isdigit(look))
	{
		token.value = getNum();
		token.sym = NUMBER;
	}
	else if(std::isalpha(look))
	{
		token.value = getName();
		token.sym = IDENT;
	}
	else if(isOp(look))
	{
		token.value = getOp();
		token.sym = OPERATOR;
	}
	else if(look == '(')
	{
		token.sym = LBR;
		getChar();
	}
	else if(look == ')')
	{
		token.sym = RBR;
		getChar();
	}
	else if(look == '\"')
	{
		token.value = getString();
		token.sym = STRING;
	}
	else
	{
		token.value += look;
		getChar();
	}

	skipWhite();
	return token;
}

void Lexer::getChar()
{
	ss.get(look);
}

void Lexer::match(char c)
{
	if(look == c)
		getChar();
	else
	{
		char msg[64];
		sprintf(msg, "Expected %c", c);
		throw std::runtime_error(msg);
	}
	skipWhite();
}

void Lexer::skipWhite()
{
	while(iswhite(look))
		getChar();
}

void Lexer::skipComma()
{
	skipWhite();
	if(look == ',')
	{
		getChar();
		skipWhite();
	}
}

std::string Lexer::getName()
{
	if(!std::isalpha(look))
		throw std::runtime_error("Expected name");
	std::string name;
	name += look;
	getChar();

	while(std::isalnum(look) || look == '_')
	{
		name += look;
		getChar();
	}

	skipWhite();
	return name;
}

std::string Lexer::getNum()
{
	if(!std::isdigit(look))
		throw std::runtime_error("Expected number");
	std::string num;
	num += look;
	getChar();
	while(std::isdigit(look))
	{
		num += look;
		getChar();
	}
	if(look == '.')
	{
		num += look;
		getChar();
		while(std::isdigit(look))
		{
			num += look;
			getChar();
		}
	}
	skipWhite();

	return num;
}

std::string Lexer::getOp()
{
	if(!isOp(look))
		throw std::runtime_error("Expected operator");
	std::string op;
	op += look;
	getChar();
	while(isOp(look))
	{
		op += look;
		getChar();
	}
	skipWhite();

	return op;
}

std::string Lexer::getString()
{
	match('\"');
	std::string str;
	str += look;
	getChar();
	while(look != '\"')
	{
		str += look;
		getChar();
	}
	match('\"');
	skipWhite();

	return str;
}

void Lexer::init()
{
	getChar();
}