#include "AccessControlCreate.h"

FLT_PREOP_CALLBACK_STATUS
AccessControlCreatePreOperation(
	_Inout_ PFLT_CALLBACK_DATA Data,
	_In_ PCFLT_RELATED_OBJECTS FltObjects,
	_Flt_CompletionContext_Outptr_ PVOID *CompletionContext
) {
	NTSTATUS status = FLT_PREOP_SUCCESS_WITH_CALLBACK;
	
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(CompletionContext);

	// We are only processing IRP operations
	if (FALSE == FLT_IS_IRP_OPERATION(Data)) {
		status = FLT_PREOP_SUCCESS_NO_CALLBACK;
		goto PreCreateCleanUP;
	}

PreCreateCleanUP:
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