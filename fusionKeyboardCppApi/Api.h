#pragma once
#include "libusb.h"
#include "Status.h"

class Api
{
private:
	libusb_context* _ctx = NULL;
	libusb_device_handle* _dev_handle = NULL;
	double compute_elapsed_time(timeval start, timeval end);
	bool is_valid_rgb_keyboard(libusb_device* device);
	libusb_device_handle* get_device_handle();
	int initDevice();
	int initLibusb();

public:
	int Init();
	int Uninit();
	int GetCurrentMode(t_status*);
};

