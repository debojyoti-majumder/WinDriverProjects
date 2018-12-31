#include "AccessControlSetup.h"
#include "GlobalData.h"
#include "FilterContexts.h"

NTSTATUS PopulateInstanceContext(
	PCTX_INSTANCE_CONTEXT instanceContext
) {
	PAGED_CODE();

	NTSTATUS status = STATUS_SUCCESS;
	ULONG dwBuffNeeded = 0;
	PUNICODE_STRING volumeName = NULL;

	status = FltGetVolumeName(instanceContext->Volume, NULL, &dwBuffNeeded);
	if (status == STATUS_BUFFER_TOO_SMALL) {
		volumeName = ExAllocatePool(NonPagedPool, dwBuffNeeded);
		status = FltGetVolumeName(instanceContext->Volume, volumeName, &dwBuffNeeded);

		if (STATUS_SUCCESS == status) {
			instanceContext->VolumeName = volumeName;
		}
		else {
			ExFreePool(volumeName);
		}
	}

	return status;
}

NTSTATUS
AccessControlInstanceSetup(
	IN PCFLT_RELATED_OBJECTS		FltObjects,
	IN FLT_INSTANCE_SETUP_FLAGS		Flags,
	IN DEVICE_TYPE					VolumeDeviceType,
	IN FLT_FILESYSTEM_TYPE			VolumeFilesystemType
) {
	UNREFERENCED_PARAMETER(Flags);
	PAGED_CODE();

	NTSTATUS status = STATUS_SUCCESS;
	BOOLEAN isSnapshopVolume = FALSE;
	PCTX_INSTANCE_CONTEXT instanceContext = NULL;

	// Do not attach to Network FS
	if (FILE_DEVICE_NETWORK_FILE_SYSTEM == VolumeDeviceType) {
		return STATUS_FLT_DO_NOT_ATTACH;
	}

	// Do not attach to MUP also
	if (FLT_FSTYPE_MUP == VolumeFilesystemType || FLT_FSTYPE_RAW == VolumeFilesystemType ) {
		DbgPrint("Filter: Not attaching to the Volume\n");
		return STATUS_FLT_DO_NOT_ATTACH;
	}

	// Do not attach to snapshot volume
	status = FltIsVolumeSnapshot(FltObjects->Volume, &isSnapshopVolume);
	if (NT_SUCCESS(status) && isSnapshopVolume) {
		DbgPrint("Filter: Not attaching to snapshot volume\n");
		return STATUS_FLT_DO_NOT_ATTACH;
	}

	// Allocating and getting the insatnce context
	status = FltAllocateContext(FltObjects->Filter, FLT_INSTANCE_CONTEXT, 
				CTX_INSTANCE_CONTEXT_SIZE, NonPagedPool, &instanceContext);

	DbgPrint("Filter: Attaching to volume\n");

	if (NT_SUCCESS(status)) {
		// Setting up the instance context
		instanceContext->Volume = FltObjects->Volume;
		instanceContext->Instance = FltObjects->Instance;
		status = PopulateInstanceContext(instanceContext);

		// Setting up the filter context
		if (NT_SUCCESS(status)) {
			status = FltSetInstanceContext(FltObjects->Instance, 
						FLT_SET_CONTEXT_KEEP_IF_EXISTS,
						instanceContext, 
						NULL);
		}
	}

	return status;
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