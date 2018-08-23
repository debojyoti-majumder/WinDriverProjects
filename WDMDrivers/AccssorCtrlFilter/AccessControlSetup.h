#pragma once

#include <fltKernel.h>

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

#ifdef ALLOC_PRAGMA
	#pragma alloc_text(PAGE, AccessControlInstanceSetup)
#endif