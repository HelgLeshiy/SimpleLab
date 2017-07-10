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

	void operatorMapInit();

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
	static void popTreeLeft(Node *&node);

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

	void printTree(Node *node, int depth = 0)
	{
		if (!node) return;
		for (int i = 0; i < depth; ++i)
			std::cout << "  ";
		std::cout << node->token.value << "\n";
		for (auto& arg : node->args)
			printTree(arg, depth+1);
	}

private:
	void init();
	Token curTok;

	bool hasVarName;
	std::string lastVar;
	std::stringstream ss;

	Namescope *ns;
	Lexer lexer;

	static std::map<std::string, std::function<void(Node *&left, Node *&right)>> backOperators;
};