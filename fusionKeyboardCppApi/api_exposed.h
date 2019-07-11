#pragma once

#ifdef API_EXPORTS
#define API_API __declspec(dllexport)
#else
#define API_API __declspec(dllimport)
#endif
#include "Status.h"


extern "C" API_API int dllexp_InitApi();

extern "C" API_API int dllexp_UninitApi();

extern "C" API_API int dllexp_GetCurrentMode(t_status*);