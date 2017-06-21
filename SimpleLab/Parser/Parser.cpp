#include "Parser.h"
#include <cmath>

std::map<std::string, std::function<void(Parser::Node *&left, Parser::Node *&right)>> Parser::backOperators;

void Parser::operatorMapInit()
{
	backOperators["+"] = [this](Node *&left, Node *&right) 
	{
		if (!findUnknownVar(left->args[0]))
			std::swap(left->args[0], left->args[1]);

		Node *newRightRoot = new Node;
		newRightRoot->token = Token(OPERATOR, "-");

		newRightRoot->args.push_back(right);
		newRightRoot->args.push_back(left->args[1]);

		popTreeLeft(left);

		right = newRightRoot;
	};

	backOperators["-"] = [this](Node *&left, Node *&right)
	{
		if (!findUnknownVar(left->args[0]))
		{
			Node *newRightRoot = new Node;
			newRightRoot->token = Token(OPERATOR, "-");

			Node *addNode = new Node;
			addNode->token = Token(NUMBER, "0");

			newRightRoot->args.push_back(addNode);
			newRightRoot->args.push_back(right);

			right = newRightRoot;

			std::swap(left->args[0], left->args[1]);
		}

		Node *newRightRoot = new Node;
		newRightRoot->token = Token(OPERATOR, "+");

		newRightRoot->args.push_back(right);
		newRightRoot->args.push_back(left->args[1]);

		popTreeLeft(left);

		right = newRightRoot;
	};

	backOperators["*"] = [this](Node *&left, Node *&right)
	{
		if (!findUnknownVar(left->args[0]))
			std::swap(left->args[0], left->args[1]);

		Node *newRightRoot = new Node;
		newRightRoot->token = Token(OPERATOR, "/");

		newRightRoot->args.push_back(right);
		newRightRoot->args.push_back(left->args[1]);

		popTreeLeft(left);

		right = newRightRoot;
	};

	backOperators["/"] = [this](Node *&left, Node *&right)
	{
		if (!findUnknownVar(left->args[0]))
		{
			Node *newRightRoot = new Node;
			newRightRoot->token = Token(OPERATOR, "/");

			Node *addNode = new Node;
			addNode->token = Token(NUMBER, "1");

			newRightRoot->args.push_back(addNode);
			newRightRoot->args.push_back(right);

			right = newRightRoot;

			std::swap(left->args[0], left->args[1]);
		}

		Node *newRightRoot = new Node;
		newRightRoot->token = Token(OPERATOR, "*");

		newRightRoot->args.push_back(right);
		newRightRoot->args.push_back(left->args[1]);

		popTreeLeft(left);

		right = newRightRoot;
	};

	backOperators["^"] = [this](Node *&left, Node *&right)
	{
		if (findUnknownVar(left->args[0]))
		{
			Node *newRightBranch = new Node;
			newRightBranch->token = Token(OPERATOR, "/");
			Node *one = new Node;
			one->token = Token(NUMBER, "1");

			newRightBranch->args.push_back(one);
			newRightBranch->args.push_back(left->args[1]);

			Node *newRightRoot = new Node;
			newRightRoot->token = Token(OPERATOR, "^");

			newRightRoot->args.push_back(right);
			newRightRoot->args.push_back(newRightBranch);
			right = newRightRoot;

			popTreeLeft(left);
		}
		else if (findUnknownVar(left->args[1]))
		{
			Node *newRightRoot = new Node;
			newRightRoot->token = Token(IDENT, "log");

			newRightRoot->args.push_back(right);
			newRightRoot->args.push_back(left->args[0]);
			right = newRightRoot;

			std::swap(left->args[0], left->args[1]);
			popTreeLeft(left);
		}
		
	};
}

double Parser::parse(const std::string& input, Namescope *scope)
{
	Node *leftTree = nullptr;
	Node *rightTree = nullptr;

	ns = scope;
	size_t ePos = input.find('=');
	if (ePos != std::string::npos)
	{
		leftTree = createTree(input.substr(0, ePos));
		rightTree = createTree(input.substr(ePos + 1, input.length() - 1));
	}
	else
	{
		rightTree = createTree(input);
		leftTree = new Node;
		leftTree->token.sym = IDENT;
		leftTree->token.value = "ans";
	}

	bool varInLeft = findUnknownVar(leftTree);
	bool varInRight = findUnknownVar(rightTree);

	if (!varInLeft && !varInRight)
		throw std::runtime_error("There must be at least one unknown variable in equation");

	if(!varInLeft)
		std::swap(leftTree, rightTree);

	transformEquation(leftTree, rightTree);

	return calkulate(rightTree);
}

Parser::Node* Parser::createTree(const std::string& expr)
{
	lexer.startScan(expr);
	init();
	return expression();
}

double Parser::calkulate(Node *exprRoot)
{
	if (!exprRoot->args.empty())
	{
		switch (exprRoot->token.sym)
		{
		case OPERATOR:
		{
			double arg1 = calkulate(exprRoot->args[0]);
			double arg2 = calkulate(exprRoot->args[1]);
			const std::string& op = exprRoot->token.value;
			if (op == "+")		return arg1 + arg2;
			else if (op == "-")	return arg1 - arg2;
			else if (op == "*")	return arg1 * arg2;
			else if (op == "/")	return arg1 / arg2;
			else if (op == "^")	return pow(arg1,arg2);
			else throw std::runtime_error("Unknown operator " + op);
		} break;

		case IDENT:
		{
			std::vector<std::shared_ptr<Value>> params;

			for (auto &it : exprRoot->args)
			{
				if (it->token.sym == STRING)
				{
					std::shared_ptr<Value> value(std::make_shared< TypedValue<std::string> >());
					dynamic_cast<TypedValue<std::string>*>(value.get())->value = it->token.value;
					params.push_back(value);
				}
				else
				{
					std::shared_ptr<Value> value(std::make_shared< TypedValue<double> >());
					dynamic_cast<TypedValue<double>*>(value.get())->value = calkulate(it);
					params.push_back(value);
				}
			}

			auto lookup = ns->lookupFunc(exprRoot->token.value, exprRoot->args.size());
			if (lookup == Namescope::LookupResult::not_found)
				throw std::runtime_error("unknown function");
			if (lookup == Namescope::LookupResult::wrong_signature)
				throw std::runtime_error("signature mismatch for function");
			return ns->getFunc(exprRoot->token.value)->function(ns, params);
		} break;

		default:
			break;
		}
	}
	else
	{
		switch (exprRoot->token.sym)
		{
		case NUMBER:
		{
			return atof(exprRoot->token.value.c_str());
		} break;

		case IDENT:
		{
			auto lookup = ns->lookupVar(exprRoot->token.value);
			if (lookup == Namescope::LookupResult::not_found)
				throw std::runtime_error("unknown variable");
			return dynamic_cast<TypedValue<double>*>(ns->getVar(exprRoot->token.value).get())->value;
		} break;
			
		default:
			break;
		}
	}

	return 0;
}

bool Parser::findUnknownVar(Node *node)
{
	if (!node) return false;
	if (node->token.sym == IDENT && ns->lookupVar(node->token.value) != Namescope::found)
		return true;

	for (auto &it : node->args)
		if (findUnknownVar(it))
			return true;

	return false;
}

void Parser::transformEquation(Node *&left, Node *&right)
{
	while (!(left->token.sym == IDENT && ns->lookupVar(left->token.value) == Namescope::not_found))
	{
		backOperators[left->token.value](left, right);
	}
}

void Parser::popTreeLeft(Node *&node)
{
	Node *buf = node->args[0];
	delete node;

	node = buf;
}

void Parser::getToken()
{
	curTok = lexer.scan();
}

void Parser::init()
{
	getToken();
}

Parser::Node*  Parser::expression()
{
	Node *root = nullptr;
	Node *left = term();

	while(curTok.sym == OPERATOR && isaddop(curTok.value))
	{
		Node *node = new Node;
		node->token = curTok;
		getToken();
		node->args.push_back(left);
		node->args.push_back(term());
		if (!root) root = node;
		left = node;
	}

	if (!root)
		root = left;

	return root;
}

double Parser::assigment()
{
	return 0;
}

Parser::Node*  Parser::term()
{
	Node *root = nullptr;
	Node *left = power();
	
	while(curTok.sym == OPERATOR && ismulop(curTok.value))
	{
		Node *node = new Node;
		node->token = curTok;
		getToken();
		node->args.push_back(left);
		node->args.push_back(term());
		if (!root) root = node;
		left = node;
	}

	if (!root)
		root = left;

	return root;
}

Parser::Node*  Parser::power()
{
	Node *root = nullptr;
	Node *left = factor();

	while (curTok.sym == OPERATOR && curTok.value == "^")
	{
		Node *node = new Node;
		node->token = curTok;
		getToken();
		node->args.push_back(left);
		node->args.push_back(power());
		if (!root) root = node;
		left = node;
	}

	if (!root)
		root = left;

	return root;
}

Parser::Node*  Parser::factor()
{
	Node *node = nullptr;
	if(curTok.sym == LBR)
	{
		getToken();
		node = expression();
		if(curTok.sym != RBR)
			throw std::runtime_error("Expected )");
		getToken();
	}
	else if(curTok.sym == NUMBER)
	{
		node = new Node;
		node->token = curTok;
		getToken();
	}
	else if (curTok.sym == IDENT)
	{
		node = ident();
	}
	else
	{
		char msg[64];
		sprintf(msg, "Unexpected lexem %s", curTok.value.c_str());
		throw std::runtime_error(msg);
	}

	return node;
}

void Parser::parseParams(Node *node)
{
	while(curTok.sym != RBR)
	{
		if(curTok.sym == STRING)
		{
			Node *param = new Node;
			param->token = curTok;
			getToken();
			node->args.push_back(param);
		}
		else
		{
			node->args.push_back(expression());
		}
	}

	getToken();
}

Parser::Node*  Parser::ident()
{
	std::string name = curTok.value;

	Node *node = new Node;
	node->token = curTok;

	getToken();


	if(curTok.sym == LBR)
	{
		getToken();
		std::vector<std::shared_ptr<Value>> params;
		parseParams(node);
	}

	return node;
}