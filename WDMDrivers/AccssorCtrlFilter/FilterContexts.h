#pragma once

#include <fltKernel.h>

#define CTX_INSTANCE_CONTEXT_TAG 'cIxC'

typedef struct _CTX_INSTANCE_CONTEXT {
	//  Instance for this context.
	PFLT_INSTANCE Instance;

	//  Volume associated with this instance.
	PFLT_VOLUME Volume;

	//  Name of the volume associated with this instance.
	UNICODE_STRING VolumeName;

} CTX_INSTANCE_CONTEXT, *PCTX_INSTANCE_CONTEXT;

#define CTX_INSTANCE_CONTEXT_SIZE         sizeof( CTX_INSTANCE_CONTEXT )

VOID
FilterContextCleanup(
	IN PFLT_CONTEXT Context,
	IN FLT_CONTEXT_TYPE ContextType
);