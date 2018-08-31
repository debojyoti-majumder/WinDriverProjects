#include "AccessControlSetup.h"
#include "GlobalData.h"
#include "FilterContexts.h"

NTSTATUS PopulateInstanceContext(
	PCTX_INSTANCE_CONTEXT insatnceContext
) {
	NTSTATUS status = STATUS_SUCCESS;

	UNREFERENCED_PARAMETER(insatnceContext);
	PAGED_CODE();

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
	UNREFERENCED_PARAMETER(VolumeDeviceType);

	PAGED_CODE();
	NTSTATUS status = STATUS_SUCCESS;
	BOOLEAN isSnapshopVolume = FALSE;
	PCTX_INSTANCE_CONTEXT instanceContext = NULL;

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

	// Allocating and getting the insatnce context
	status = FltAllocateContext(FltObjects->Filter, FLT_INSTANCE_CONTEXT, 
				CTX_INSTANCE_CONTEXT_SIZE, NonPagedPool, &instanceContext);

	DbgPrint("Filter: Attaching to volume\n");

	if (NT_SUCCESS(status)) {
		status = PopulateInstanceContext(instanceContext);

		if (NT_SUCCESS(status)) {
			DbgPrint("Filter: Setting the filter context");

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