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

	// Registering the filter driver
	status = FltRegisterFilter(	DriverObject,				// The driver object
								&FilterRegistration,		// IRP_MJ Callbacks
								&controllerData.Filter);	// The handle for this filter driver

	// If failed can not proceed
	if ( !NT_SUCCESS(status) || controllerData.Filter == NULL ) {
		DbgPrint("Filter: Failed to register filter driver\n");
		return status;
	}

	// Starting the filtering process
	// TODO: Make regsitry option if to start on connect or not
	status = FltStartFiltering(controllerData.Filter);
	if (!NT_SUCCESS(status)) {
		DbgPrint("Filter: Can not start filtering\n");
		FltUnregisterFilter(controllerData.Filter);
	}

	DbgPrint("Filter: Driver Entry done\n");
	
	return status;
}
