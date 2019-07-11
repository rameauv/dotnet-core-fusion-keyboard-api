#pragma once
#include "Api.h"
#include <inttypes.h>
#include "enums.h"

class Commands
{
private:
	static void fin_header(header_t* hdr);
public:
	static int set_mode(libusb_device_handle* handle, uint8_t mode, uint8_t color, uint8_t brightness, uint8_t speed);
	static int get_current_mode(libusb_device_handle* handle, t_mode* status);
	static int set_custom_mode(libusb_device_handle* handle, uint8_t* data);
};
