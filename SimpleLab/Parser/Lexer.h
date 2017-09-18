/**
 * \file	Lexer.h
 * \brief	Заголовочный файл с описанием класса Lexer
 *
 * Данный файл содержит в себе определения основных
 * классов и структур, используемых для лексического анализа
 */
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

/// Список возможных символов, составляющих операторы
const std::string OPERATORS = ",+-*/=<>!^.";

/// Набор возможных типов Лексемы
enum SymType
{
	IDENT,			///< Идентификатор
	NUMBER,			///< Число
	STRING,			///< Строка
	OPERATOR,		///< Оператор
	LBR = ')',		///< Закрывающая круглая скобка
	RBR = '(',		///< Открывающая круглая скобка
	LSQRBR = '[',	///< Открывающая квадратная скобка
	RSQRBR = ']'	///< Закрывающая круглая скобка 
};

/**
 * \brief Токен, определяющий тип и значение лексемы
 */
struct Token
{
	Token() = default;
	Token(SymType _sym, const std::string& val) : sym(_sym), value(val) { }

	SymType sym;		///< Тип лексемы
	std::string value;	///< Значение лексемы

	Token& operator= (const Token& other) { sym = other.sym; value = other.value; return *this; }
};

/**
 * \brief Класс лексического анализатора
 * 
 * Позволяет разбивать входящий поток символов на отдельные лексемы,
 * согласно синтаксису математического языка.
 */
class Lexer
{
public:

	/**
	 * Указывает синтаксическому анализатору строку для анализа
	 *
	 * \param[in] input входной буффер
	 */
	void startScan(const std::string& input);

	/**
	* Извлекает очередную лексему
	*
	* \return очередная лексема
	*/
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