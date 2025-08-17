#pragma once
#include "Core/IApplication.h"
#include <type_traits>

class Credentials;

template<class T, typename ...Args>
inline T& IApplication::create(Args ... args) {
	static_assert(std::is_base_of<Object, T>::value, "T has to inherit from Object!");

	// create new object
	T* p_obj = new T(Credentials(), this, args...);
	p_obj->onInitialize();

	registerObject(p_obj);
	return *p_obj;
}