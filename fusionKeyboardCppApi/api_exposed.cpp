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

int dllexp_GetCurrentMode(t_status* status)
{
	int r = API.GetCurrentMode(status);
	//printf("exposed: mode:%d\nspeed:%d\nbrightness:%d\ncolor:%d\n", status->mode, status->speed, status->brightness, status->color);
	return r;
}