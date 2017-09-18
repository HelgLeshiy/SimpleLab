#include "vec_math.h"
#include <functional>

std::vector<float> vectorOperation(const std::vector<float>& a, const std::vector<float>& b, std::function<float(float, float)> op, float filler = 0)
{
	const std::vector<float> *less = &a;
	const std::vector<float> *greater = &b;

	if (b.size() < a.size())
		std::swap(less, greater);

	std::vector<float> res(greater->size());

	for (int i = 0; i < less->size(); ++i)
		res[i] = op(a[i], b[i]);

	for (int i = less->size(); i < greater->size(); ++i)
		if (less == &a)
			res[i] = op(filler, b[i]);
		else
			res[i] = op(a[i], filler);

	return res;
}

std::vector<float> operator+(const std::vector<float>& a, const std::vector<float>& b)
{
	return vectorOperation(a, b, [](float x, float y) { return x + y; });
}

std::vector<float> operator-(const std::vector<float>& a, const std::vector<float>& b)
{
	return vectorOperation(a, b, [](float x, float y) { return x - y; });
}

std::vector<float> operator*(const std::vector<float>& a, const std::vector<float>& b)
{
	return vectorOperation(a, b, [](float x, float y) { return x * y; }, 1);
}

std::vector<float> operator*(float a, const std::vector<float>& b)
{
	std::vector<float> res(b.size());
	for (int i = 0; i < res.size(); ++i)
		res[i] = a * b[i];

	return res;
}

std::vector<float> operator*(const std::vector<float>& a, float b)
{
	std::vector<float> res(a.size());
	for (int i = 0; i < res.size(); ++i)
		res[i] = a[i] * b;

	return res;
}

std::vector<float> operator/(const std::vector<float>& a, const std::vector<float>& b)
{
	return vectorOperation(a, b, [](float x, float y) { return x / y; }, 1);
}

std::vector<float> operator/(const std::vector<float>& a, float b)
{
	std::vector<float> res(a.size());
	for (int i = 0; i < res.size(); ++i)
		res[i] = a[i] / b;

	return res;
}

float scalar(const std::vector<float>& a, const std::vector<float>& b)
{
	std::vector<float> c = a * b;

	float res = 0;
	for (int i = 0; i < c.size(); ++i)
		res += c[i];

	return res;
}