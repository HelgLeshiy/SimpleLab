/**
 * \file	value_math.h
 * \brief	Заголовочный файл с описанием простейших 
 * математических операций для типа Value
 */
#pragma 
#pragma once
#include "Namescope.h"

Value* plus(Value* a, Value* b);
Value* minus(Value* a, Value* b);
Value* multiplyElem(Value* a, Value* b);
Value* multiply(Value* a, Value* b);
Value* divideElem(Value* a, Value* b);
Value* divide(Value* a, Value* b);
Value* pow(Value* a, Value* b);