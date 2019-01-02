#pragma once

#include <fltKernel.h>
#include "FilterContexts.h"

NTSTATUS
AccessControlInstanceSetup(
	IN PCFLT_RELATED_OBJECTS		FltObjects,
	IN FLT_INSTANCE_SETUP_FLAGS		Flags,
	IN DEVICE_TYPE					VolumeDeviceType,
	IN FLT_FILESYSTEM_TYPE			VolumeFilesystemType
);

NTSTATUS
AccessControlUnload(
	IN FLT_FILTER_UNLOAD_FLAGS Flags
);

static NTSTATUS PopulateInstanceContext(
	PCTX_INSTANCE_CONTEXT insatnceContext
);

NTSTATUS
InstanceQueryTeardown(
	_In_ PCFLT_RELATED_OBJECTS FltObjects,
	_In_ FLT_INSTANCE_QUERY_TEARDOWN_FLAGS Flags
);

#ifdef ALLOC_PRAGMA
	#pragma alloc_text(PAGE, AccessControlInstanceSetup)
	#pragma alloc_text(PAGE, PopulateInstanceContext)
#endif
