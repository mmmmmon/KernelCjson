#include "cJSON.h"
#include "kcrt.h"

void UnLoadDriver(PDRIVER_OBJECT pDriverObj)
{
	UNREFERENCED_PARAMETER(pDriverObj);
}

HANDLE OpenFile(wchar_t* filepath)
{
    NTSTATUS ntStatus;
    HANDLE fileHandle = NULL;
    OBJECT_ATTRIBUTES objectAttributes = { 0 };
    IO_STATUS_BLOCK ioStatusBlock = { 0 };
    UNICODE_STRING unicode_filename = { 0 };
    RtlInitUnicodeString(&unicode_filename, filepath);
    do
    {
        InitializeObjectAttributes(&objectAttributes, &unicode_filename, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);
        ntStatus = ZwOpenFile(&fileHandle,
            GENERIC_ALL,
            &objectAttributes,
            &ioStatusBlock,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            FILE_SYNCHRONOUS_IO_NONALERT);
        if (NT_SUCCESS(ntStatus) == FALSE)
        {
            break;
        }
    } while (FALSE);
    return fileHandle;
}
ULONG GetFileSize(HANDLE pFileHandle)
{
    NTSTATUS ntStatus;
    FILE_STANDARD_INFORMATION fileInformation;
    IO_STATUS_BLOCK ioStatusBlock = { 0 };
    ULONG file_size = 0;
    do
    {
        if (pFileHandle == NULL)
        {
            break;
        }
        ntStatus = ZwQueryInformationFile(pFileHandle, &ioStatusBlock, &fileInformation, sizeof(FILE_STANDARD_INFORMATION), FileStandardInformation);
        if (NT_SUCCESS(ntStatus) == FALSE)
        {
            break;
        }
        file_size = (ULONG)fileInformation.EndOfFile.QuadPart;
    } while (FALSE);
    return file_size;
}
NTSTATUS ReadFile(HANDLE pFileHandle, void* buffer, unsigned long size)
{
    NTSTATUS ntStatus;
    LARGE_INTEGER byteOffset;
    byteOffset.QuadPart = 0;
    IO_STATUS_BLOCK ioStatusBlock = { 0 };

    do
    {
        if (pFileHandle == NULL || buffer == NULL)
        {
            ntStatus = STATUS_BAD_DATA;
            break;
        }
        ntStatus = ZwReadFile(pFileHandle, NULL, NULL, NULL, &ioStatusBlock, buffer, size, &byteOffset, NULL);
    } while (FALSE);
    return ntStatus;
}
NTSTATUS CloseFile(HANDLE pFileHandle)
{
    return ZwClose(pFileHandle);
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObj, PUNICODE_STRING pRegistryPath)
{
	UNREFERENCED_PARAMETER(pRegistryPath);
	pDriverObj->DriverUnload = UnLoadDriver;
    __debugbreak();
    HANDLE handle = OpenFile(L"\\??\\C:\\Users\\zdj\\Desktop\\test.json");
    if (handle)
    {
        ULONG fileSize = GetFileSize(handle);
        if (fileSize != 0)
        {
            __debugbreak();
            void* buffer = ExAllocatePoolWithTag(NonPagedPool, fileSize+1, 'tag');
	    memset(buffer,0,fileSize+1);//why plus one? because the jcson will call strlen to get all buffer size,if the final str is no zero,this function will cross the border
            if (buffer != NULL)
            {
                if (NT_SUCCESS(ReadFile(handle, buffer, fileSize)))
                {
                    cJSON* json = cJSON_Parse(buffer);
                    cJSON* ddd1 = cJSON_GetObjectItem(json, "ddd1");
                    unsigned long long dd1x = ddd1->valueulong;
                    char* dd2x = cJSON_GetObjectItem(json, "ddd2")->valuestring;
                    dd1x = 0;
                    dd2x = NULL;
                    if (json != NULL)
                    {
                        cJSON_Delete(json);
                    }
                }
                ExFreePoolWithTag(buffer, 'tag');
            }
        }
        CloseFile(handle);
    }
	return STATUS_SUCCESS;
}
