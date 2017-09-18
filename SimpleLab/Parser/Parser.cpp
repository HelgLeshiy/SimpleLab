#include "Parser.h"
#include <cmath>
#include <algorithm>
#include "value_math.h"

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

	backOperators["*."] = [this](Node *&left, Node *&right)
	{
		if (!findUnknownVar(left->args[0]))
			std::swap(left->args[0], left->args[1]);

		Node *newRightRoot = new Node;
		newRightRoot->token = Token(OPERATOR, "/.");

		newRightRoot->args.push_back(right);
		newRightRoot->args.push_back(left->args[1]);

		popTreeLeft(left);

		right = newRightRoot;
	};

	backOperators["/."] = [this](Node *&left, Node *&right)
	{
		if (!findUnknownVar(left->args[0]))
		{
			Node *newRightRoot = new Node;
			newRightRoot->token = Token(OPERATOR, "/.");

			Node *addNode = new Node;
			addNode->token = Token(NUMBER, "1");

			newRightRoot->args.push_back(addNode);
			newRightRoot->args.push_back(right);

			right = newRightRoot;

			std::swap(left->args[0], left->args[1]);
		}

		Node *newRightRoot = new Node;
		newRightRoot->token = Token(OPERATOR, "*.");

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

Value* Parser::parse(app *appPtr, const std::string& input, Namescope *scope)
{
	m_appPtr = appPtr;

	Node *leftTree = nullptr;
	Node *rightTree = nullptr;

	ns = scope;
	size_t ePos = input.find('=');
	size_t semicolonPos = input.find(';');
	if (ePos != std::string::npos)
	{
		leftTree = createTree(input.substr(0, ePos));
		rightTree = createTree(input.substr(ePos + 1, semicolonPos == std::string::npos ? input.length() - ePos - 1 : semicolonPos - ePos - 1));
	}
	else
	{
		rightTree = createTree(input);
		leftTree = new Node;
		leftTree->token.sym = IDENT;
		leftTree->token.value = "ans";
	}

	std::cout << "Left tree:\n";
	printTree(leftTree);
	std::cout << "\n\Right tree:\n";
	printTree(rightTree);

	bool varInLeft = findUnknownVar(leftTree);
	bool varInRight = findUnknownVar(rightTree);

	if (!varInLeft && !varInRight)
	{
		if (leftTree->token.sym == IDENT && ns->lookupFunc(leftTree->token.value, leftTree->args.size()) == Namescope::not_found)
		{
			ns->eraseVar(leftTree->token.value);
			varInLeft = true;
		}
		else if (semicolonPos != std::string::npos)
		{
			std::string pivotVar = input.substr(semicolonPos + 1, input.length() - 1);
			size_t i;
			while ((i = pivotVar.find(' ')) != std::string::npos)
				pivotVar.erase(i, 1);

			ns->eraseVar(pivotVar);
			varInLeft = findUnknownVar(leftTree);
		}
		else
			throw std::runtime_error("There must be at least one unknown variable in equation");
	}
		
	if(!varInLeft)
		std::swap(leftTree, rightTree);

	transformEquation(leftTree, rightTree);

	Value *res = calkulate(rightTree);
	ns->setVar(res, leftTree->token.value);
	lastVar = leftTree->token.value;

	return res;
}

Parser::Node* Parser::createTree(const std::string& expr)
{
	lexer.startScan(expr);
	init();
	return expression();
}

Value *Parser::calkulate(Node *exprRoot)
{
	if (!exprRoot->args.empty())
	{
		switch (exprRoot->token.sym)
		{
		case OPERATOR:
		{
			Value *arg1 = calkulate(exprRoot->args[0]);
			Value *arg2 = calkulate(exprRoot->args[1]);
			const std::string& op = exprRoot->token.value;
			if (op == "+")		return plus(arg1, arg2);
			else if (op == "-")	return minus(arg1, arg2);
			else if (op == "*.") return multiplyElem(arg1, arg2);
			else if (op == "*") return multiply(arg1, arg2);
			else if (op == "/") return divide(arg1, arg2);
			else if (op == "^")	return pow(arg1,arg2);
			else throw std::runtime_error("Unknown operator " + op);
		} break;

		case IDENT:
		{
			std::vector<Value*> params;

			for (auto &it : exprRoot->args)
			{
				if (it->token.sym == STRING)
				{
					params.push_back(new TypedValue<std::string>('s', it->token.value));
				}
				else
				{
					params.push_back(new TypedValue<float>('f', ((TypedValue<float>*)calkulate(it))->value));
				}
			}

			auto lookup = ns->lookupFunc(exprRoot->token.value, exprRoot->args.size());
			if (lookup == Namescope::LookupResult::not_found)
				throw std::runtime_error("unknown function");
			if (lookup == Namescope::LookupResult::wrong_signature)
				throw std::runtime_error("signature mismatch for function");
			return ns->getFunc(exprRoot->token.value)->function(m_appPtr, ns, params);
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
			return new TypedValue<float>('f', atof(exprRoot->token.value.c_str()));
		} break;

		case IDENT:
		{
			auto lookup = ns->lookupVar(exprRoot->token.value);
			if (lookup == Namescope::LookupResult::not_found)
				throw std::runtime_error("unknown variable");
			return ns->getVar(exprRoot->token.value);
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
	if (node->token.sym == IDENT && ns->lookupFunc(node->token.value, node->args.size()) != Namescope::found && ns->lookupVar(node->token.value) != Namescope::found)
		return true;

	for (auto &it : node->args)
		if (findUnknownVar(it))
			return true;

	return false;
}

void Parser::transformEquation(Node *&left, Node *&right)
{
	while (!(left->token.sym == IDENT && left->args.size() == 0))
	{
		if (ns->lookupFunc(left->token.value, left->args.size()) == Namescope::found)
		{
			Node *newRightRoot = new Node;
			newRightRoot->token = Token(IDENT, ns->getBackFunction(left->token.value));

			newRightRoot->args.push_back(right);

			popTreeLeft(left);

			right = newRightRoot;
		}
		else
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
