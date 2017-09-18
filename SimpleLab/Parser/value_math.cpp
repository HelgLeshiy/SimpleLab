#include "value_math.h"
#include <stdexcept>
#include "vec_math.h"

Value* plus(Value* a, Value* b)
{
	if (a->valueType == b->valueType)
	{
		switch (a->valueType)
		{
		case 'f':
			return new TypedValue<float>('f', ((TypedValue<float>*)a)->value + ((TypedValue<float>*)b)->value);

		case 'v':
			return new TypedValue<std::vector<float>>('v', ((TypedValue<std::vector<float>>*)a)->value + ((TypedValue<std::vector<float>>*)b)->value);

		case 's':
			return new TypedValue<std::string>('s', ((TypedValue<std::string>*)a)->value + ((TypedValue<std::string>*)b)->value);
		}
	}
	else
		throw std::runtime_error("Argument type mismatch in operator +");
}

Value* minus(Value* a, Value* b)
{
	if (a->valueType == b->valueType)
	{
		switch (a->valueType)
		{
		case 'f':
			return new TypedValue<float>('f', ((TypedValue<float>*)a)->value - ((TypedValue<float>*)b)->value);

		case 'v':
			return new TypedValue<std::vector<float>>('v', ((TypedValue<std::vector<float>>*)a)->value - ((TypedValue<std::vector<float>>*)b)->value);

		case 's':
		{
			size_t pos = ((TypedValue<std::string>*)a)->value.find(((TypedValue<std::string>*)b)->value);
			if (pos != std::string::npos)
				return new TypedValue<std::string>('s', ((TypedValue<std::string>*)a)->value.erase(pos, ((TypedValue<std::string>*)b)->value.length()));
			else
				return new TypedValue<std::string>('s', ((TypedValue<std::string>*)a)->value);
		}
		}
	}
	else
		throw std::runtime_error("Argument type mismatch in operator -");
}

Value* multiplyElem(Value* a, Value* b)
{
	if (a->valueType == 'v' && b->valueType == 'v')
		return new TypedValue<std::vector<float>>('v', ((TypedValue<std::vector<float>>*)a)->value * ((TypedValue<std::vector<float>>*)b)->value);

	return multiply(a, b);
}

Value* multiply(Value* a, Value* b)
{
	if (a->valueType == 'f' && b->valueType == 'f')
		return new TypedValue<float>('f', ((TypedValue<float>*)a)->value * ((TypedValue<float>*)b)->value);

	if (a->valueType == 'f' && b->valueType == 'v')
		return new TypedValue<std::vector<float>>('v', ((TypedValue<float>*)a)->value * ((TypedValue<std::vector<float>>*)b)->value);

	if (a->valueType == 'v' && b->valueType == 'f')
		return new TypedValue<std::vector<float>>('v', ((TypedValue<std::vector<float>>*)a)->value * ((TypedValue<float>*)b)->value);

	throw std::runtime_error("Argument type mismatch in operator *");
}

Value* divideElem(Value* a, Value* b)
{
	if (a->valueType == 'v' && b->valueType == 'v')
		return new TypedValue<std::vector<float>>('v', ((TypedValue<std::vector<float>>*)a)->value / ((TypedValue<std::vector<float>>*)b)->value);

	return divide(a, b);
}

Value* divide(Value* a, Value* b)
{
	if (a->valueType == 'f' && b->valueType == 'f')
		return new TypedValue<float>('f', ((TypedValue<float>*)a)->value / ((TypedValue<float>*)b)->value);

	if (a->valueType == 'v' && b->valueType == 'f')
		return new TypedValue<std::vector<float>>('v', ((TypedValue<std::vector<float>>*)a)->value / ((TypedValue<float>*)b)->value);

	throw std::runtime_error("Argument type mismatch in operator /");
}

Value* pow(Value* a, Value* b)
{
	if (a->valueType == 'f' && b->valueType == 'f')
		return new TypedValue<float>('f', pow(((TypedValue<float>*)a)->value, ((TypedValue<float>*)b)->value));

	throw std::runtime_error("Argument type mismatch in operator ^");
}