#pragma once

#include <fltKernel.h>

#include "AccessControlSetup.h"
#include "AccessControlCreate.h"

#define USERCOMM_PORT_NAME L"\\AccessControlPort"

typedef struct _ACCESSCONTROLER_DATA {
	PDRIVER_OBJECT	DriverObject;
	PFLT_PORT		ServerPort;
	PFLT_PORT		ClientPort;
	PFLT_FILTER		Filter;
}ACCESSCONTROLER_DATA, *PACCESSCONTROLER_DATA;

CONST FLT_OPERATION_REGISTRATION Callbacks[] = {
	{ IRP_MJ_CREATE,
	0,
	AccessControlCreatePreOperation,
	AccessControlCreatePostOperation },

	{ IRP_MJ_OPERATION_END }
};


CONST FLT_REGISTRATION FilterRegistration = {

	sizeof(FLT_REGISTRATION),			//  Size
	FLT_REGISTRATION_VERSION,           //  Version
	0,                                  //  Flags

	NULL,                               //  Context
	Callbacks,                          //  Operation callbacks

	AccessControlUnload,				//  MiniFilterUnload

	AccessControlInstanceSetup,			//  InstanceSetup
	NULL,								//  InstanceQueryTeardown
	NULL,								//  InstanceTeardownStart
	NULL,								//  InstanceTeardownComplete

	NULL,                               //  GenerateFileName
	NULL,                               //  GenerateDestinationFileName
	NULL                                //  NormalizeNameComponent
};

ACCESSCONTROLER_DATA controllerData;