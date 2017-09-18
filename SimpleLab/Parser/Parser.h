/**
 * \file	Parser.h
 * \brief	Заголовочный файл с описанием класса парсера
 *
 * Данный файл содержит в себе определения основных
 * классов и структур, используемых для парсера математических выражений 
 */
#pragma once

#include "Namescope.h"
#include "Lexer.h"


/**
 * \brief Определение класса Parser
 *
 * Используется для анализа входящей строки с математическим выражением,
 * решения уравнений и вычисления значений 
 */
class Parser
{
public:
	/**
	 * Вычисляет значение выражения
	 * 
	 * \param[in,out]	appPtr	Указатель на класс приложения
	 * \param[in]		input	Строка с выражением
	 * \param[in,out]	scope	Область видимости с предустановленными функциями
	 *							и переменными
	 *
	 * \return Результат вычислений
	 */
	Value* parse(app *appPtr, const std::string& input, Namescope *scope);

	/**
	 * Возвращает имя вычесленной переменной или ans, если не определено
	 *
	 * \return Имя вычесленной переменной
	 */
	const std::string& getLastVar() const { return lastVar; }

	/**
	 * Инициализирует операторы и обратные операторы для решения уравнений.
	 * Внимание! Необходим вызов перед использованием класса.
	 */
	void operatorMapInit();

private:
	struct Node
	{
		Token token;
		std::vector<Node*> args;
	};

	Node* createTree(const std::string& expr);
	Value* calkulate(Node *exprRoot);
	bool findUnknownVar(Node *node);
	void transformEquation(Node *&left, Node *&right);
	static void popTreeLeft(Node *&node);

	void getToken();

	bool isaddop(const std::string& s) { return s == "+" || s == "-"; }
	bool ismulop(const std::string& s) { return s == "*" || s == "/" || s == "*."; }

	Node* expression();
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

	app *m_appPtr = nullptr;
	Namescope *ns;
	Lexer lexer;

	static std::map<std::string, std::function<void(Node *&left, Node *&right)>> backOperators;
};
