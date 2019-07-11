#include "pch.h"
#include <windows.h>
#include "api_exposed.h"
#include "Api.h"
#include <cstdio>

Api API;

int dllexp_InitApi() {
	return API.Init();
}

int dllexp_UninitApi()
{
	return API.Uninit();
}

int dllexp_GetCurrentMode(t_mode* mode)
{
	return API.GetCurrentMode(mode);
}

int dllexp_SetMode(t_mode* mode)
{
	return API.SetMode(mode);
}