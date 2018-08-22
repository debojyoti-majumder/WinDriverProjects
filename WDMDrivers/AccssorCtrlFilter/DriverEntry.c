#include <fltKernel.h>

DRIVER_INITIALIZE DriverEntry;

#ifdef ALLOC_PRAGMA
	#pragma alloc_text(INIT, DriverEntry)
#endif // ALLOC_PRAGMA


NTSTATUS 
DriverEntry(
	IN PDRIVER_OBJECT DriverObject,
	IN PUNICODE_STRING RegistryPath
) {
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	return STATUS_SUCCESS;
}