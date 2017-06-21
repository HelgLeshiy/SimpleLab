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

	static void operatorMapInit();

private:
	struct Node
	{
		Token token;
		std::vector<Node*> args;
	};

	Node* createTree(const std::string& expr);
	double calkulate(Node *exprRoot);
	bool findUnknownVar(Node *node);
	void transformEquation(Node *&left, Node *&right);

	void getToken();

	bool isaddop(const std::string& s) { return s == "+" || s == "-"; }
	bool ismulop(const std::string& s) { return s == "*" || s == "/"; }

	Node* expression();
	double assigment();
	Node* term();
	Node* power();
	Node* factor();
	Node* ident();
	void parseParams(Node *node);

private:
	void init();
	Token curTok;

	bool hasVarName;
	std::string lastVar;
	std::stringstream ss;

	Namescope *ns;
	Lexer lexer;

	static std::map<std::string, std::string> backOperators;
};