#pragma once

#include <map>
#include <string>
#include <functional>
#include <vector>
#include <set>

/**
*	Value struct interface.
**/
struct Value
{
	virtual ~Value() { }
};

/**
*	Template implementation for a Value type
**/
template <typename T>
struct TypedValue : public Value
{
	TypedValue() { }
	TypedValue(T v) : value(v) { }
	virtual ~TypedValue() { }
	T value;
};

class ActivationRecord;

/**
*	Definition for a preinstalled math function.
*
*	field function: real function pointer with a vector of arguments
*	field argnum: the argument count
**/
struct InstalledFunction
{
	std::function<double(const std::vector<std::shared_ptr<Value>>&)> function;
    int argnum;
};


/**
*	Namescope - class defines the number of preinstalled functions
*	and variables.
*	You also can build a namescope tree with a outer constructor.
*	All child namescope has access to parent scopes.
**/
class Namescope
{
public:
    Namescope() : p_outer(nullptr) { }

	/**
	*	Child namescope constructor
	*	param	outer	parent namescope
	**/
    Namescope(const Namescope* outer) : p_outer(outer) { }

	/**
	*	Lookup codes
	**/
	enum LookupResult { not_found, wrong_signature, found };

	/**
	*	Search for a function in this namescope
	*
	*	param	name	The function name
	*	param	nargs	The number of agruments
	*
	*	return	The result of search
	**/
    LookupResult lookupFunc(std::string name, int nargs) const;

	/**
	*	Search for a variable in this namescope
	*
	*	param	name	The variable name
	*
	*	return	The result of search
	**/
    LookupResult lookupVar(std::string name) const;

	/**
	*	Install a new function in this namescope
	*
	*	param	f		The function pointer
	*	param	argnum	The number of agruments
	*	param	name	The name of this function
	**/
    void installFunction(std::function<double(const std::vector<std::shared_ptr<Value>>&)> f, int argnum, std::string name);

	/**
	*	Install a new variable in this namescope
	*
	*	param	v		The variable interface pointer
	*	param	name	The name of this variable
	**/
    void installVar(std::shared_ptr<Value> v, std::string name);

	/**
	*	Returns a function pointer
	*
	*	param	name	The name of function
	*	return	The function pointer
	**/
    std::shared_ptr<InstalledFunction> getFunc(std::string name) const;

	/**
	*	Returns a value pointer
	*
	*	param	name	The name of variable
	*	return	The value pointer
	**/
    std::shared_ptr<Value> getVar(std::string name) const;

private:
    const Namescope* p_outer;
    std::map<std::string, std::shared_ptr<InstalledFunction>> functions;
    std::map<std::string, std::shared_ptr<Value>> vars;
};
