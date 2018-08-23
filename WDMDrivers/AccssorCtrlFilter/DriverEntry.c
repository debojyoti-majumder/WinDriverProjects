#include <fltKernel.h>
#include "RegistrationData.h"

DRIVER_INITIALIZE DriverEntry;

#ifdef ALLOC_PRAGMA
	#pragma alloc_text(INIT, DriverEntry)
#endif // ALLOC_PRAGMA


NTSTATUS
AccessControlInstanceSetup(
	IN PCFLT_RELATED_OBJECTS		FltObjects,
	IN FLT_INSTANCE_SETUP_FLAGS	Flags,
	IN DEVICE_TYPE				VolumeDeviceType,
	IN FLT_FILESYSTEM_TYPE		VolumeFilesystemType
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
AccessControllerUnload(
	_In_ FLT_FILTER_UNLOAD_FLAGS Flags
) {
	UNREFERENCED_PARAMETER(Flags);

	DbgPrint("AscCtrl: UnRegistering the driver");

	// Cleaning up the global handles
	//FltCloseCommunicationPort(controllerData.ServerPort);
	//FltUnregisterFilter(controllerData.Filter);

	return STATUS_SUCCESS;
}

FLT_PREOP_CALLBACK_STATUS
AccessControlCreatePreOperation(
	_Inout_ PFLT_CALLBACK_DATA Data,
	_In_ PCFLT_RELATED_OBJECTS FltObjects,
	_Flt_CompletionContext_Outptr_ PVOID *CompletionContext
) {
	NTSTATUS status = FLT_PREOP_SUCCESS_WITH_CALLBACK;

	UNREFERENCED_PARAMETER(Data);
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(CompletionContext);

	return status;
}

FLT_POSTOP_CALLBACK_STATUS
AccessControlCreatePostOperation(
	_Inout_ PFLT_CALLBACK_DATA Data,
	_In_ PCFLT_RELATED_OBJECTS FltObjects,
	_In_opt_ PVOID CompletionContext,
	_In_ FLT_POST_OPERATION_FLAGS Flags
) {
	UNREFERENCED_PARAMETER(Data);
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(CompletionContext);
	UNREFERENCED_PARAMETER(Flags);

	return FLT_POSTOP_FINISHED_PROCESSING;
}

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

	AccessControllerUnload,				//  MiniFilterUnload

	AccessControlInstanceSetup,			//  InstanceSetup
	NULL,								//  InstanceQueryTeardown
	NULL,								//  InstanceTeardownStart
	NULL,								//  InstanceTeardownComplete

	NULL,                               //  GenerateFileName
	NULL,                               //  GenerateDestinationFileName
	NULL                                //  NormalizeNameComponent
};

NTSTATUS 
DriverEntry(
	IN PDRIVER_OBJECT DriverObject,
	IN PUNICODE_STRING RegistryPath
) {
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	return STATUS_SUCCESS;
}
