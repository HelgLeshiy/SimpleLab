#include "Namescope.h"

Namescope::LookupResult Namescope::lookupFunc(std::string name, int nargs) const
{
    auto psig = functions.find(name);
    auto found = psig != functions.end();
	if (found && psig->second->argnum == nargs)
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

void Namescope::installFunction(std::function<double(Namescope*, const std::vector<std::shared_ptr<Value>>&)> f, int argnum, std::string name)
{
    InstalledFunction* pf = new InstalledFunction;
    pf->function = f;
    pf->argnum = argnum;
    functions.insert(make_pair(name, std::shared_ptr<InstalledFunction>(pf)));
}

void Namescope::installVar(std::shared_ptr<Value> v, std::string name)
{
    vars.insert(std::make_pair(name, v));
}

std::shared_ptr<InstalledFunction> Namescope::getFunc(std::string name) const
{
    auto pfunc = functions.find(name);
    if (pfunc != functions.end())
        return pfunc->second;
    if (p_outer != nullptr)
        return p_outer->getFunc(name);
    return nullptr;
}

std::shared_ptr<Value> Namescope::getVar(std::string name) const
{
    auto pvar = vars.find(name);
    if (pvar != vars.end())
        return pvar->second;
    if (p_outer != nullptr)
        return p_outer->getVar(name);
    return nullptr;
}