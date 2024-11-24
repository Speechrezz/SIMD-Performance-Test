#pragma once

#define RegisterOverloadsDeclarations(D, A) \
	inline Register<D, A> operator+(const Register<D, A>& other) const; \
	inline Register<D, A> operator-(const Register<D, A>& other) const; \
	inline Register<D, A> operator*(const Register<D, A>& other) const; 


#define RegisterOverloadsDefinitions(D, A) \
	inline Register<D, A> Register<D, A>::operator+(const Register<D, A>& other) const \
	{ \
		return add(*this, other); \
	} \
	inline Register<D, A> Register<D, A>::operator-(const Register<D, A>& other) const \
	{ \
		return sub(*this, other); \
	} \
	inline Register<D, A> Register<D, A>::operator*(const Register<D, A>& other) const \
	{ \
		return mul(*this, other); \
	} 