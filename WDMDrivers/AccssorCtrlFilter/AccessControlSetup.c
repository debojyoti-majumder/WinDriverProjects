#include "AccessControlSetup.h"
#include "GlobalData.h"

NTSTATUS
AccessControlInstanceSetup(
	IN PCFLT_RELATED_OBJECTS		FltObjects,
	IN FLT_INSTANCE_SETUP_FLAGS		Flags,
	IN DEVICE_TYPE					VolumeDeviceType,
	IN FLT_FILESYSTEM_TYPE			VolumeFilesystemType
) {
	UNREFERENCED_PARAMETER(Flags);
	UNREFERENCED_PARAMETER(VolumeDeviceType);

	PAGED_CODE();
	NTSTATUS status;
	BOOLEAN isSnapshopVolume = FALSE;

	// Do not attach to MUP also
	if (FLT_FSTYPE_MUP == VolumeFilesystemType ) {
		DbgPrint("Filter: Not attaching to the Volume\n");
		return STATUS_FLT_DO_NOT_ATTACH;
	}

	// Do not attach to snapshot volume
	status = FltIsVolumeSnapshot(FltObjects->Volume, &isSnapshopVolume);
	if (NT_SUCCESS(status) && isSnapshopVolume) {
		DbgPrint("Filter: Not attaching to snapshot volume\n");
		return STATUS_FLT_DO_NOT_ATTACH;
	}

	DbgPrint("Filter: Attaching to volume\n");
	return STATUS_SUCCESS;
}

NTSTATUS
AccessControlUnload(
	IN FLT_FILTER_UNLOAD_FLAGS Flags
) {
	UNREFERENCED_PARAMETER(Flags);

	DbgPrint("Filter: UnRegistering the driver\n");

	// Cleaning up the global handles
	// FltCloseCommunicationPort(controllerData.ServerPort);
	FltUnregisterFilter(controllerData.Filter);

	return STATUS_SUCCESS;
}