#pragma once

#include <map>
#include <string>
#include <functional>
#include <vector>
#include <set>

struct Value
{
	virtual ~Value() { }
};

template <typename T>
struct TypedValue : public Value
{
	TypedValue() { }
	TypedValue(T v) : value(v) { }
	virtual ~TypedValue() { }
	T value;
};

class ActivationRecord;

struct InstalledFunction
{
	std::function<double(const std::vector<std::shared_ptr<Value>>&)> function;
    int argnum;
};

class Namescope
{
    const Namescope* p_outer;
    std::map<std::string, std::shared_ptr<InstalledFunction>> functions;
    std::map<std::string, std::shared_ptr<Value>> vars;

public:
    Namescope() : p_outer(nullptr) { }
    Namescope(const Namescope* outer) : p_outer(outer) { }

	enum LookupResult { not_found, wrong_signature, found };

    LookupResult lookupFunc(std::string name, int nargs) const;
    LookupResult lookupVar(std::string name) const;
    void installFunction(std::function<double(const std::vector<std::shared_ptr<Value>>&)> f, int argnum, std::string name);
    void installVar(std::shared_ptr<Value> v, std::string name);
    std::shared_ptr<InstalledFunction> getFunc(std::string name) const;
    std::shared_ptr<Value> getVar(std::string name) const;
};