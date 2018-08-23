#include "AccessControlSetup.h"

NTSTATUS
AccessControlInstanceSetup(
	IN PCFLT_RELATED_OBJECTS		FltObjects,
	IN FLT_INSTANCE_SETUP_FLAGS		Flags,
	IN DEVICE_TYPE					VolumeDeviceType,
	IN FLT_FILESYSTEM_TYPE			VolumeFilesystemType
) {
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(Flags);
	UNREFERENCED_PARAMETER(VolumeFilesystemType);

	PAGED_CODE();

	// This is to exclude certain filsystem
	if (FILE_DEVICE_DISK_FILE_SYSTEM != VolumeDeviceType) {
		DbgPrint("Not attaching to the Volume");
		return STATUS_FLT_DO_NOT_ATTACH;
	}

	return STATUS_SUCCESS;
}

NTSTATUS
AccessControlUnload(
	IN FLT_FILTER_UNLOAD_FLAGS Flags
) {
	UNREFERENCED_PARAMETER(Flags);

	DbgPrint("Filter: UnRegistering the driver");

	// Cleaning up the global handles
	// FltCloseCommunicationPort(controllerData.ServerPort);
	// FltUnregisterFilter(controllerData.Filter);

	return STATUS_SUCCESS;
}