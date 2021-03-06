#include "Namescope.h"

Namescope::LookupResult Namescope::lookupFunc(std::string name, int nargs) const
{
    auto psig = functions.find(name);
    auto found = psig != functions.end();
	if (found && psig->second->argTypes.length() == nargs)
        return LookupResult::found;
    if (p_outer != nullptr)
    {
        auto outer_result = p_outer->lookupFunc(name, nargs);
        if (outer_result != LookupResult::not_found)
            return outer_result;
    }
    return found ? LookupResult::wrong_signature : LookupResult::not_found;
}

Namescope::LookupResult Namescope::lookupVar(std::string name) const
{
    if (vars.find(name) != vars.end())
        return LookupResult::found;
    if (p_outer != nullptr)
        return p_outer->lookupVar(name);
    return LookupResult::not_found;
}

void Namescope::installFunction(std::function<Value*(app* appPtr, Namescope*, const std::vector<Value*>&)> f, char retType, const std::string& argTypes, std::string name)
{
    InstalledFunction* pf = new InstalledFunction;
    pf->function = f;
    pf->retType = retType;
	pf->argTypes = argTypes;
    functions.insert(make_pair(name, pf));
}

void Namescope::registerBackFunction(const std::string& functionName, const std::string& backFunctionName)
{
	backFunctions[functionName] = backFunctionName;
}

const std::string& Namescope::getBackFunction(const std::string& functionName)
{
	if (backFunctions.find(functionName) == backFunctions.end())
		return "";
	
	return backFunctions[functionName];
}

void Namescope::setVar(Value* v, std::string name)
{
	vars[name] = v;
}

InstalledFunction* Namescope::getFunc(std::string name) const
{
    auto pfunc = functions.find(name);
    if (pfunc != functions.end())
        return pfunc->second;
    if (p_outer != nullptr)
        return p_outer->getFunc(name);
    return nullptr;
}

Value* Namescope::getVar(std::string name) const
{
    auto pvar = vars.find(name);
    if (pvar != vars.end())
        return pvar->second;
    if (p_outer != nullptr)
        return p_outer->getVar(name);
    return nullptr;
}

void Namescope::eraseVar(const std::string& name)
{
	vars.erase(name);
}
