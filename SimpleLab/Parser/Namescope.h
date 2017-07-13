#pragma once

#include <map>
#include <string>
#include <functional>
#include <vector>
#include <set>
#include <memory>

class app;

class NoValue { };

/**
*	Value struct interface.
**/
struct Value
{
	Value(char type) : valueType(type) { }
	virtual ~Value() { }
	char valueType;
};

/**
*	Template implementation for a Value type
**/
template <typename T>
struct TypedValue : public Value
{
	TypedValue(char type) : Value(type) { }
	TypedValue(char type, T v) : Value(type), value(v) { }
	virtual ~TypedValue() { }
	T value;
};

class Namescope;

/**
*	Definition for a preinstalled math function.
*
*	field function: real function pointer with a vector of arguments
*	field argnum: the argument count
*	field argTypes: the argument types if "printf" style
**/
struct InstalledFunction
{
	std::function<Value*(app* appPtr, Namescope*, const std::vector<Value*>&)> function;
	char retType;
	std::string argTypes;
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
    void installFunction(std::function<Value*(app* appPtr, Namescope*, const std::vector<Value*>&)> f, char retType, const std::string& argTypes, std::string name);

	/**
	*	Register a new back function in this namescope
	*
	*	param	functionName		The the name of direct function
	*	param	backFunctionName	The the name of backward function
	**/
	void registerBackFunction(const std::string& functionName, const std::string& backFunctionName);

	/**
	*	Returns a backward function name
	*
	*	param	functionName		The the name of direct function
	*
	*	return the name of backward function or "" if not exist
	**/
	const std::string& getBackFunction(const std::string& functionName);

	/**
	*	Sets a variable in this namescope
	*
	*	param	v		The variable interface pointer
	*	param	name	The name of this variable
	**/
	void setVar(Value* v, std::string name);

	/**
	*	Returns a function pointer
	*
	*	param	name	The name of function
	*	return	The function pointer
	**/
    InstalledFunction* getFunc(std::string name) const;

	/**
	*	Returns a value pointer
	*
	*	param	name	The name of variable
	*	return	The value pointer
	**/
    Value* getVar(std::string name) const;

	void eraseVar(const std::string& name);

	std::map<std::string, InstalledFunction*>::const_iterator functionsBegin() const { return functions.cbegin(); }
	std::map<std::string, InstalledFunction*>::const_iterator functionsEnd() const { return functions.cend(); }

private:
    const Namescope* p_outer;
    std::map<std::string, InstalledFunction*> functions;
	std::map<std::string, std::string> backFunctions;
    std::map<std::string, Value*> vars;
};
