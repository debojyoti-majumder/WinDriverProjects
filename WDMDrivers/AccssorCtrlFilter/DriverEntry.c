#include <fltKernel.h>

#include "RegistrationData.h"
#include "GlobalData.h"

DRIVER_INITIALIZE DriverEntry;

#ifdef ALLOC_PRAGMA
	#pragma alloc_text(INIT, DriverEntry)
#endif // ALLOC_PRAGMA


NTSTATUS 
DriverEntry(
	IN PDRIVER_OBJECT DriverObject,
	IN PUNICODE_STRING RegistryPath
) {
	UNREFERENCED_PARAMETER(RegistryPath);

	NTSTATUS status = STATUS_SUCCESS;
	controllerData.Filter = NULL;

	status = FltRegisterFilter(	DriverObject,				// The driver object
								&FilterRegistration,		// IRP_MJ Callbacks
								&controllerData.Filter);	// The handle for this filter driver

	if ( !NT_SUCCESS(status) || controllerData.Filter == NULL ) {
		DbgPrint("Filter: Failed to register filter driver");
	}

	DbgPrint("Filter: Driver Entry done");

	return status;
}
