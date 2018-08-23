#pragma once

#include <fltKernel.h>

typedef struct _ACCESSCONTROLER_DATA {
	PDRIVER_OBJECT	DriverObject;
	PFLT_PORT		ServerPort;
	PFLT_PORT		ClientPort;
	PFLT_FILTER		Filter;
}ACCESSCONTROLER_DATA, *PACCESSCONTROLER_DATA;

ACCESSCONTROLER_DATA controllerData;