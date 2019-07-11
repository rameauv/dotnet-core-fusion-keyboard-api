#include "pch.h"
#include "commands.h"
#include "libusb.h"
#include <cstdio>
#include "enums.h"

void ::Commands::fin_header(header_t* hdr) {
	hdr->reserved = 0;
	uint16_t chksumtmp = 0;
	uint8_t* data = (uint8_t*)hdr;
	for (uint8_t i = 0; i < 7; i++) {
		chksumtmp += data[i];
	}
	hdr->checksum = (uint8_t)(0xff - (chksumtmp & 0xff));
}

int Commands::set_mode(libusb_device_handle* handle, uint8_t mode, uint8_t color, uint8_t brightness, uint8_t speed) {
	header_t header;
	header.kind = KIND_PRESET;
	header.reserved = RESERVED1;
	header.mode = 0x33;
	header.speedLength = 0x05;
	header.brightness = 0x32;
	header.color = 0x02;
	header.reserved2 = 0x01;
	fin_header(&header);

	int r = libusb_control_transfer(handle, 0x21, 0x09, 0x0300, 0x0003, (uint8_t*)& header, 0x0008, 0);
	if (r < 0) {
		printf("Control transfer 1 failed! %d\n", r);
		return -1;
	}
	else {
		// printf("Control transfer 1 OK!\n");
	}

	header.mode = mode;
	header.speedLength = speed;
	header.brightness = brightness;
	header.color = color;
	header.reserved2 = 0;
	fin_header(&header);
	r = libusb_control_transfer(handle, 0x21, 0x09, 0x0300, 0x0003, (uint8_t*)& header, 0x0008, 0);
	if (r < 0) {
		printf("Control transfer 2 failed! %d\n", r);
		return -1;
	}
	else {
		// printf("Control transfer 2 OK!\n");
	}
	return 0;
}

int Commands::get_current_mode(libusb_device_handle* handle, t_mode* status)
{
	header_t header;
	header.kind = 0x88;
	header.reserved = 0x00;
	header.mode = 0x00;
	header.speedLength = 0x00;
	header.brightness = 0x00;
	header.color = 0x00;
	header.reserved2 = 0x00;
	fin_header(&header);
	int r = libusb_control_transfer(handle, 0x21, 0x09, 0x0300, 0x0003, (uint8_t*)& header, 0x0008, 0);
	if (r < 0) {
		printf("Control transfer 2 failed! %d\n", r);
		return -1;
	}
	else {
		// printf("Control transfer 2 OK!\n");
	}

	header.kind = 0x00;
	header.reserved = 0x00;
	header.mode = 0x00;
	header.speedLength = 0x00;
	header.brightness = 0x00;
	header.color = 0x00;
	header.reserved2 = 0x00;
	header.checksum = 0x00;

	r = libusb_control_transfer(handle, 0xa1, 0x01, 0x0300, 0x0003, (uint8_t*)& header, 0x0008, 0);
	if (r < 0) {
		printf("Control transfer 1 failed! %d\n", r);
		return -1;
	}
	else {
		// printf("Control transfer 1 OK!\n");
	}
	status->mode = header.mode;
	status->speed = header.speedLength;
	status->brightness = header.brightness;
	status->color = header.color;
	return 0;
}

int Commands::set_custom_mode(libusb_device_handle* handle, uint8_t* data) {
	header_t header;
	header.kind = KIND_CUSTOM_CONFIG;
	header.reserved = RESERVED1;
	header.mode = 1;
	header.speedLength = 8;
	header.brightness = 0;
	header.color = 0;
	header.reserved2 = RESERVED1;
	fin_header(&header);

	int r = libusb_control_transfer(handle, 0x21, 0x09, 0x0300, 0x0003, (uint8_t*)& header, 0x0008, 0);
	if (r < 0) {
		printf("Control transfer 1 failed! %d\n", r);
		return -1;
	}
	else {
		// printf("Control transfer 1 OK!\n");
	}

	for (uint8_t i = 0; i < 8; i++) {
		int transferred = 0;
		r = libusb_interrupt_transfer(handle, (6 | LIBUSB_ENDPOINT_OUT), data + (i * 64), 64, &transferred, 0);
		if (r < 0 || transferred != 64) {
			printf("Interrupt transfer %d failed", i);
		}
	}
	// printf("Interrupt transfers OK!\n");

	header.kind = KIND_PRESET;
	header.reserved = RESERVED1;
	header.mode = 0x34;
	header.speedLength = 0x05;
	header.brightness = 0x32;
	header.color = 0x02;
	header.reserved2 = 0x01;
	fin_header(&header);

	r = libusb_control_transfer(handle, 0x21, 0x09, 0x0300, 0x0003, (uint8_t*)& header, 0x0008, 0);
	if (r < 0) {
		printf("Control transfer 2 failed! %d\n", r);
		return -1;
	}
	else {
		// printf("Control transfer 2 OK!\n");
	}
	return 0;
}