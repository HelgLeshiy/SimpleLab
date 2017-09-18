#pragma once

#include <map>
#include <string>
#include <functional>
#include <vector>
#include <set>
#include <memory>

class app;

/**
 * \brief Пустой тип
 */
class NoValue { };

/**
 * \brief Интерфейс класса Значение
 **/
struct Value
{
	Value(char type) : valueType(type) { }
	virtual ~Value() { }
	char valueType; ///< Тип переменной ('f', 's', 'n', ...)
};

/**
 * \brief Шаблонная реализация класса Value
 */
template <typename T>
struct TypedValue : public Value
{
	TypedValue(char type) : Value(type) { }
	TypedValue(char type, T v) : Value(type), value(v) { }
	virtual ~TypedValue() { }
	T value; ///< Хранимое значение
};

class Namescope;

/**
*	\brief Определение предустановленной математической функции
*
*	field function: real function pointer with a vector of arguments
*	field argnum: the argument count
*	field argTypes: the argument types if "printf" style
**/
struct InstalledFunction
{
	std::function<Value*(app* appPtr, Namescope*,
		                 const std::vector<Value*>&)> function; ///< Указатель на функцию
	char retType;			///< Тип возвращаемого значения ('f', 's', 'n', ...)
	std::string argTypes;	///< Типы аргументов
};


/**
 *	\brief Namescope - класс определяющий набор предустановленных функций
 *	и переменных
 *	
 *	Вы также можете создать область иерархию областей видимости с помощью 
 *	конструктора, принимающего внешний Namescope.
 *
 *	Все области-потомки имеют доступ к внешним областям видимости.
 */
class Namescope
{
public:
    Namescope() : p_outer(nullptr) { }

	/**
	 *	Конструктор для локальных областей видимости
	 *
	 *	\param[in]	outer	Родительский namescope
	 */
    Namescope(const Namescope* outer) : p_outer(outer) { }

	/**
	 *	Перечисление результатов поиска
	 */
	enum LookupResult { not_found, wrong_signature, found };

	/**
	 *	Поиск функций в данной области
	 *
	 *	\param[in]	name	Имя функции
	 *	\param[in]	nargs	Количество аргументов
	 *
	 *	\return	Результат поиска
	 */
    LookupResult lookupFunc(std::string name, int nargs) const;

	/**
	 *	Поиск переменной в данной области
	 *
	 *	\param[in]	name	Имя переменной
	 *
	 *	\return	Результат поиска
	 */
    LookupResult lookupVar(std::string name) const;

	/**
	 *	Установка новой функции
	 *
	 *	\param[in]	f			Указатель на функцию
	 *	\param[in]	retType		Тип возвращаемого значения
	 *	\param[in]	argTypes	Типы аргументов
	 *	\param[in]	name		Имя новой функции
	 */
    void installFunction(std::function<Value*(app* appPtr, Namescope*,
		                                      const std::vector<Value*>&)> f,
						 char retType,
						 const std::string& argTypes,
						 std::string name);

	/**
	 *	Указание обратной функции
	 *
	 *	\param[in]	functionName		Имя прямой функции
	 *	\param[in]	backFunctionName	Имя обратной к ней функции
	 */
	void registerBackFunction(const std::string& functionName, 
							  const std::string& backFunctionName);

	/**
	 *	Возвращяет имя обратной функции
	 *
	 *	\param[in]	functionName		Имя прямой функции
	 *
	 *	\return Имя обратной функции или "", если ее не существует
	 */
	const std::string& getBackFunction(const std::string& functionName);

	/**
	 *	Устанавливает значение переменной
	 *
	 *	\param[in]	v		Указатель на переменную
	 *	\param[in]	name	The name of this variable
	 */
	void setVar(Value* v, std::string name);

	/**
	 *	Возвращает указатель на функцию
	 *
	 *	\param[in]	name	Имя функции
	 *
	 *	\return Указатель на функцию или nullptr, если такой нет
	 */
    InstalledFunction* getFunc(std::string name) const;

	/**
	 *	Возвращает указатель на переменную
	 *
	 *	\param[in]	name	Имя переменной
	 *
	 *	\return Указатель на переменную или nullptr, если такой нет
	 */
    Value* getVar(std::string name) const;

	/**
	 *	Удаляет переменную
	 *
	 *	\param[in]	name	Имя переменной
	 */
	void eraseVar(const std::string& name);

	/**
	 *	Доступ к итереторам на хранимые функции
	 */
	std::map<std::string, InstalledFunction*>::const_iterator functionsBegin() const { return functions.cbegin(); }
	std::map<std::string, InstalledFunction*>::const_iterator functionsEnd() const { return functions.cend(); }

private:
    const Namescope* p_outer;
    std::map<std::string, InstalledFunction*> functions;
	std::map<std::string, std::string> backFunctions;
    std::map<std::string, Value*> vars;
};
