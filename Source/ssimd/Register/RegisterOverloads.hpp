#pragma once

#define RegisterOverloadsDeclarations(Register) \
	inline Register operator+(const Register& other) const; \
	inline Register operator-(const Register& other) const; \
	inline Register operator*(const Register& other) const; \


#define RegisterOverloadsDefinitions(Register) \
	inline Register Register::operator+(const Register& other) const \
	{ \
		return add(*this, other); \
	} \
	inline Register Register::operator-(const Register& other) const \
	{ \
		return sub(*this, other); \
	} \
	inline Register Register::operator*(const Register& other) const \
	{ \
		return mul(*this, other); \
	} \