#include "TouchInput.h"

TouchInput::TouchInput(const std::string &device_name, TouchEventCallback callback, int samples, int slots) : device_name(device_name), samples(samples), slots(slots), event_callback(callback)
{
	TS_SETENV(TSLIB_CALIBFILE);
	TS_SETENV(TSLIB_CONFFILE);
	TS_SETENV(TSLIB_TSDEVICE);

	ts = ts_setup(device_name.c_str(), 1);

	if (!ts)
	{
		throw TouchInputException("Couldn't initialize ts inputs.");
	}

	samp_mt = new ts_sample_mt *[samples];
	for (int i = 0; i < samples; i++)
	{
		samp_mt[i] = new ts_sample_mt[slots];
	}
	//samp_mt = std::vector<std::vector<ts_sample_mt>>(samples, std::vector<ts_sample_mt>(slots));
}

TouchInput::~TouchInput()
{
	for (int i = 0; i < samples; i++)
	{
		delete[] samp_mt[i];
	}
	delete[] samp_mt;

	// Using std::vector<std::vector> leads to a SIGABRT (memory leak somewhere?)
	// Had to switch to a plain multidimensional array
	// Probably the library, on ts_close, attempts to free the memory I initialized
	// which is a fairly serious issue, but until fixed, we do it this way
	ts_close(ts);
}

void TouchInput::setTouchEventCallback(TouchEventCallback callback)
{
	this->event_callback = callback;
}

void TouchInput::poll()
{
	ret = ts_read_mt(ts, samp_mt, slots, samples);

	if (ret < 0)
		return;

	for (int i = 0; i < ret; i++)
	{
		for (int j = 0; j < slots; j++)
		{
#ifdef TSLIB_MT_VALID
			if (!(samp_mt[i][j].valid & TSLIB_MT_VALID))
				continue;
#else
			if (samp_mt[i][j].valid < 1)
				continue;
#endif
			event_callback(samp_mt[i][j]);
		}
	}
}
