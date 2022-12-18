#include "kcrt.h"
#include "kcrt_defect.h"
#define KCRT_POOL_DEFAULT_TAG	'kcrt'

typedef struct _MALLOC_HEADER
{
	ULONG32 Tags;
	ULONG32 _Resv0;
	ULONG_PTR Size;
}MALLOC_HEADER, * PMALLOC_HEADER;
C_ASSERT(sizeof(MALLOC_HEADER) % sizeof(void*) == 0);

PMALLOC_HEADER GET_MALLOC_HEADER(PVOID ptr) {
	return (MALLOC_HEADER*)((PUCHAR)ptr - sizeof(MALLOC_HEADER));
}

PVOID GET_MALLOC_ADDRESS(PMALLOC_HEADER header) {
	return (PVOID)((PUCHAR)header + sizeof(MALLOC_HEADER));
}

ULONG_PTR GET_MALLOC_SIZE(PVOID ptr) {
	PMALLOC_HEADER header = GET_MALLOC_HEADER(ptr);

	if (header->Tags != KCRT_POOL_DEFAULT_TAG)
		KeBugCheckEx(BAD_POOL_HEADER, 0, 0, 0, 0);

	return header->Size;
}

#pragma warning(disable:28251)

_Check_return_ _CRT_JIT_INTRINSIC _CRTIMP
int __cdecl isalpha(_In_ int _C)
{
	return ((_C >= 'a' && _C <= 'z') || (_C >= 'A' && _C <= 'Z') ? 1 : 0);
}

__declspec(noalias)
_ACRTIMP _CRT_HYBRIDPATCHABLE
void __cdecl free(void* ptr) 
{
	if (ptr) {
		MALLOC_HEADER* mhdr = GET_MALLOC_HEADER(ptr);

		if (mhdr->Tags != KCRT_POOL_DEFAULT_TAG)
			KeBugCheckEx(BAD_POOL_HEADER, 0, 0, 0, 0);

		ExFreePool(mhdr);
	}
}

__declspec(noalias)
_ACRTIMP _CRT_HYBRIDPATCHABLE
void* __cdecl malloc(size_t size) {
	PMALLOC_HEADER mhdr = NULL;
	const size_t new_size = size + sizeof(MALLOC_HEADER);

	mhdr = (PMALLOC_HEADER)ExAllocatePoolWithTag(NonPagedPool, new_size, KCRT_POOL_DEFAULT_TAG);
	if (mhdr) {
		RtlZeroMemory(mhdr, new_size);

		mhdr->Tags = KCRT_POOL_DEFAULT_TAG;
		mhdr->Size = size;
		return GET_MALLOC_ADDRESS(mhdr);
	}

	return NULL;
}

__declspec(noalias)
_ACRTIMP _CRT_HYBRIDPATCHABLE
void* __cdecl realloc(void* ptr, size_t new_size) {
	if (!ptr) {
		return malloc(new_size);
	}
	else if (new_size == 0) {
		free(ptr);
		return NULL;
	}
	else {
		size_t old_size = GET_MALLOC_SIZE(ptr);

		if (new_size <= old_size) {
			return ptr;
		}
		else {
			void* new_ptr = malloc(new_size);

			if (new_ptr) {
				memcpy(new_ptr, ptr, old_size);
				free(ptr);
				return new_ptr;
			}
		}
	}

	return NULL;
}

#pragma warning(pop)