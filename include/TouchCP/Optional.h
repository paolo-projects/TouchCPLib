#pragma once

/**
 * @file Optional.h
 * @author Paolo Infante (info@paoloinfante.it)
 * @brief 
 * @version 1.0.0
 * @date 2020-12-17
 * 
 * Copyright (c) 2020 Paolo Infante
 * 
 */
#include <memory>

/**
 * @brief A class that wraps a value that can be null
 * 
 * @tparam T The type of the value to wrap
 */
template <typename T>
class Optional
{
public:
	/**
	 * @brief Construct an empty Optional object
	 */
	Optional() {}
	/**
	 * @brief Construct an Optional object initialized with the given value
	 * 
	 * @param value The value that will be copied
	 */
	Optional(const T &value) { innerValue = std::unique_ptr<T>(new T(value)); } // copy
	/**
	 * @brief Construct an Optional object initialized with the given value
	 * 
	 * @param value The value that will be moved
	 */
	Optional(T &&value) { innerValue = std::unique_ptr<T>(new T(std::move(value))); } // move
	/**
	 * @brief Returns true if the optional object has a value
	 * 
	 * @return whether the optional has a value
	 */
	bool hasValue() const { return innerValue != nullptr; }
	/**
	 * @brief Gets the inner object
	 * 
	 * @return T& The inner object
	 * @throws std::runtime_error if the optional does not have an object
	 */
	T &get()
	{
		T *innerPtr = innerValue.get();
		if (innerPtr != nullptr)
			return *innerPtr;
		else
			throw std::runtime_error("Can't extract a reference from a null pointer");
	}
	/**
	 * @brief Gets the inner object
	 * 
	 * @return T& The inner object
	 * @throws std::runtime_error if the optional does not have an object
	 */
	const T &get() const
	{
		T *innerPtr = innerValue.get();
		if (innerPtr != nullptr)
			return *innerPtr;
		else
			throw std::runtime_error("Can't extract a reference from a null pointer");
	}
	/**
	 * @brief Replace the inner object
	 * 
	 * @param value The object to be copied
	 */
	void set(const T &value) { innerValue.reset(new T(value)); }
	/**
	 * @brief Replace the inner object
	 * 
	 * @param value The object to be moved
	 */
	void set(T &&value) { innerValue.reset(new T(value)); }
	/**
	 * @brief Assignment operator with copy semantics
	 * 
	 * @param value The value to assign
	 * @return Optional<T>& This object
	 */
	Optional<T> &operator=(const Optional<T> &value)
	{
		if (!value.hasValue())
			innerValue.reset();
		else
			innerValue.reset(new T(value.get())); // copy
		return *this;
	}
	/**
	 * @brief Removes the inner object, making the optional void
	 * 
	 */
	void clear() { innerValue.reset(); }

private:
	std::unique_ptr<T> innerValue = nullptr;
};