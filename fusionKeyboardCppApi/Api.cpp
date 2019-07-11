#include "pch.h"
#include "Api.h"
#include <cstdio>
#include "libusb.h"
#include "enums.h"
#include <cstdlib>

double Api::compute_elapsed_time(struct timeval start, struct timeval end)
{
	return static_cast<double>(end.tv_usec - start.tv_usec) / 1000. +
		static_cast<double>(end.tv_sec - start.tv_sec) * 1000.;
}

bool Api::is_valid_rgb_keyboard(libusb_device* device)
{
	int ret;
	struct libusb_device_descriptor desc;

	ret = libusb_get_device_descriptor(device, &desc);
	if (ret < 0) {
		fprintf(stderr, "failed to get device descriptor");
		return(0);
	}
	printf("vid:%x, pid:%x\n", desc.idVendor, desc.idProduct);
	if (desc.idVendor == 0x1044 && desc.idProduct == 0x7A39)
		return 1;
	return 0;
}

libusb_device_handle* Api::get_device_handle()
{
	libusb_device** devs;
	libusb_device* device;
	ssize_t cnt;
	int r, i;
	libusb_device_handle* _dev_handle = NULL;
	int ret;

	cnt = libusb_get_device_list(NULL, &devs);
	if (cnt < 0)
		exit((int)cnt);

	for (i = 0; devs[i]; ++i) {
		if (is_valid_rgb_keyboard(devs[i]))
		{
			device = devs[i];
			ret = libusb_open(device, &_dev_handle);
			printf("ret_handle:%d\n", ret);
			if (LIBUSB_SUCCESS == ret)
			{
				return (_dev_handle);
			}
			else
				return(NULL);
		}
	}

	libusb_free_device_list(devs, 1);
	return(NULL);
}

int Api::initDevice()
{
	int r = 0;

	_dev_handle = get_device_handle();
	//_dev_handle = libusb_open_device_with_vid_pid(CTX, 0x1044, 0x7a39);
	if (_dev_handle == NULL) {
		printf("Failed to open device!\n");
		libusb_exit(_ctx);
		return 1;
	}
	//if (libusb_set_auto_detach_kernel_driver(_dev_handle, 0) < 0) {
	//  printf("Kernel ctrl driver auto detach failed.\n");
	//  goto exit;
	//}
	//if (libusb_set_auto_detach_kernel_driver(_dev_handle, 3) < 0) {
	//  printf("Kernel driver auto detach failed.\n");
	//  goto exit;
	//}

	//gettimeofday(&start, NULL);
	r = libusb_claim_interface(_dev_handle, 0);
	if (r < 0) {
		printf("Failed to claim ctrl interface! %d\n", r);
		return 4;
	}
	r = libusb_claim_interface(_dev_handle, 3);
	if (r < 0) {
		printf("Failed to claim interface! %d\n", r);
		return 2;
	}
	//gettimeofday(&end, NULL);
	//printf ("Claiming duration = %.2f ms\n", 
	//	compute_elapsed_time(start, end));

	/*if (strcmp(mode, "custom") == 0) {
	  if (argc < 3) {
		printf("Usage: %s custom file\n", argv[0]);
		exitcode = -1;
		goto exit;
	  }
	  // Custom mode
	  gettimeofday(&start, NULL);
	  FILE *fd = fopen(argv[2], "rb");
	  if (!fd) {
		printf("fopen(%s) failed: %s\n", argv[2], strerror(errno));
		exitcode = -1;
		goto exit;
	  }
	  fread(m_white_data, 512, 1, fd);
	  fclose(fd);
	  gettimeofday(&end, NULL);
	  printf ("File reading duration = %.2f ms\n",
	  compute_elapsed_time(start, end));

	  gettimeofday(&start, NULL);
	  r = set_custom_mode(_dev_handle, m_white_data);
	  gettimeofday(&end, NULL);
	  printf ("Set custom mode duration = %.2f ms\n",
	  compute_elapsed_time(start, end));

	  if (r < 0) {
		printf("Failed to set custom mode!\n");
		exitcode = -1;
		goto exit;
	  }
	  exitcode = -1;
	  goto exit;
	}*/
	return 0;
}

int Api::initLibusb()
{
	int r = libusb_init(&_ctx);
	r = libusb_set_option(_ctx, LIBUSB_OPTION_USE_USBDK);
	int exitcode = 0;
	if (r < 0) {
		printf("libusb_init error %d\n", r);
		return 1;
	}
	return 0;
}

int Api::Init() {
	int r = 0;

	_ctx = NULL;
	_dev_handle = NULL;
	r = initLibusb();
	if (r != 0)
		return r;
	r = initDevice();
	if (r != 0)
		return r;
	//r = get_current_mode(_dev_handle);
	//r = set_mode(_dev_handle, MODE_STATIC, COLOR_GREEN, 50, 8);
	printf("native: init done\n");
	return 0;
}

int Api::Uninit()
{
	libusb_release_interface(_dev_handle, 0);
	libusb_release_interface(_dev_handle, 3);
	libusb_close(_dev_handle);
	libusb_exit(_ctx);
	_ctx = NULL;
	_dev_handle = NULL;
	printf("native: uninit done\n");
	return 0;
}

int Api::GetCurrentMode(t_status* status)
{
	return (get_current_mode(this->_dev_handle, status));
}
