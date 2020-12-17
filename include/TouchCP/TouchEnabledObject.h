#pragma once
#include <functional>

#include "GraphicsObject.h"

/**
 * @brief The callback that will be called when the touch interaction happens
*/
using TouchCallback = std::function<void(void)>;

/**
 * @brief A base class that provides the methods needed for the object to
 * react to touch input
*/
class TouchEnabledObject
{
public:
	virtual int getX() const = 0;
	virtual int getY() const = 0;
	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;
	TouchCallback getTouchCallback() const
	{
		return touchEvCallback;
	}
	/**
	 * @brief Set the touch interaction callback
	 * @param cb The touch callback
	*/
	void setTouchCallback(TouchCallback cb)
	{
		touchEvCallback = cb;
	}
	/**
	 * @brief True if the object reacts to touch events
	 * @return 
	*/
	bool isTouchEnabled() const
	{
		return touchEnabled;
	}
	/**
	 * @brief Set if the object has to react to touch events
	 * @param enabled 
	*/
	void setTouchEnabled(bool enabled)
	{
		touchEnabled = enabled;
	}
	/**
	 * @brief True if the object will call the handlers of object placed below when touched.
	 * @return 
	*/
	bool isPropagateInteraction() const
	{
		return propagateInteraction;
	}
	/**
	 * @brief Set wheter the object has to call the handlers of objects placed below, when touched.
	 * @param propagate 
	*/
	void setPropagateInteraction(bool propagate)
	{
		propagateInteraction = propagate;
	}
private:
	TouchCallback touchEvCallback = nullptr;
	bool touchEnabled = true, propagateInteraction = false;
};