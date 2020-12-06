#pragma once
#include <string>
#include <tslib.h>
#include <vector>
#include <functional>

#include "TouchInputException.h"

#define TS_SETENV(x) setenv(#x, x, false);

using TouchEventCallback = std::function<void(ts_sample_mt)>; // void(*)(ts_sample_mt);

class TouchInput
{
public:
	TouchInput(const std::string& device_name, TouchEventCallback callback, int samples, int slots);
	~TouchInput();
	void setTouchEventCallback(TouchEventCallback callback);
	void poll();
private:
	std::string device_name;
	struct tsdev* ts;
	ts_sample_mt** samp_mt;
	int samples, slots, ret;
	TouchEventCallback event_callback;

	const char* TSLIB_CALIBFILE = "/etc/pointercal.tslib";
	const char* TSLIB_CONFFILE = "/etc/ts.conf";
	const char* TSLIB_TSDEVICE = "/dev/input/event0";
};

