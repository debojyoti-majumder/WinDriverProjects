#pragma once

#include <fltKernel.h>

#include "AccessControlSetup.h"
#include "AccessControlCreate.h"
#include "FilterContexts.h"

CONST FLT_OPERATION_REGISTRATION Callbacks[] = {
	{ IRP_MJ_CREATE,
	FLTFL_OPERATION_REGISTRATION_SKIP_PAGING_IO,
	AccessControlCreatePreOperation,
	AccessControlCreatePostOperation },

	{ IRP_MJ_OPERATION_END }
};

const FLT_CONTEXT_REGISTRATION ContextRegistration[] = {
	{ FLT_INSTANCE_CONTEXT,
	0,
	FilterContextCleanup,
	CTX_INSTANCE_CONTEXT_SIZE,
	CTX_INSTANCE_CONTEXT_TAG },

	{ FLT_CONTEXT_END }
};

CONST FLT_REGISTRATION FilterRegistration = {

	sizeof(FLT_REGISTRATION),			//  Size
	FLT_REGISTRATION_VERSION,           //  Version
	0,                                  //  Flags

	ContextRegistration,                //  Context
	Callbacks,                          //  Operation callbacks

	AccessControlUnload,				//  MiniFilterUnload

	AccessControlInstanceSetup,			//  InstanceSetup
	InstanceQueryTeardown,				//  InstanceQueryTeardown
	NULL,								//  InstanceTeardownStart
	NULL,								//  InstanceTeardownComplete

	NULL,                               //  GenerateFileName
	NULL,                               //  GenerateDestinationFileName
	NULL                                //  NormalizeNameComponent
};