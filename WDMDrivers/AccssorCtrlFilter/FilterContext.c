#include "FilterContexts.h"

VOID
FilterContextCleanup(
	IN PFLT_CONTEXT Context,
	IN FLT_CONTEXT_TYPE ContextType
) {
	PCTX_INSTANCE_CONTEXT pInstanceCtx;

	switch (ContextType) {
		case FLT_INSTANCE_CONTEXT:
			pInstanceCtx = (PCTX_INSTANCE_CONTEXT)Context;
			
			// Perform cleanup
			if (pInstanceCtx != NULL) {
				RtlFreeUnicodeString(&pInstanceCtx->VolumeName);
			}
			break;
		
		default:
			break;
	}
}