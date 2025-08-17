#pragma once

// declare pimpl implementation in a class with no polymorphism
#define ADD_IMPL_CLASS() \
protected: \
	class Impl; \
	Impl* mp_impl = nullptr; \
	friend class Impl; \
	virtual inline Impl& getImpl() const noexcept { \
		return *reinterpret_cast<Impl*>(mp_impl); \
	}

// declare pimpl implementation in the topmost parent class, when polymorphism is used
#define ADD_IMPL_CLASS_PARENT() ADD_IMPL_CLASS()

// declare pimpl implementation in a child class, when polymorphism is used
#define ADD_IMPL_CLASS_CHILD() \
protected: \
	class Impl; \
	friend class Impl; \
	virtual inline Impl& getImpl() const noexcept { \
		return *reinterpret_cast<Impl*>(mp_impl); \
	}

// initialize pimpl implementation
#define INIT_IMPL_CLASS(args) \
	if (mp_impl) delete mp_impl; \
	mp_impl = new Impl(args);

// access implementation
#define IMPL getImpl()


// create a member of the defining class
#define LINK_DEFINITION(name) \
private: \
	name& m_def; \
	friend class name;

// access definition
#define DEF m_def