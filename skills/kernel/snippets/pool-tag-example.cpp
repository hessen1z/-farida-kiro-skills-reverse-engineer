# Kernel Pool Tag Snippet

```cpp
#include <ntddk.h>

#define MY_TAG 'gaPM'

PVOID AllocateBuffer(SIZE_T size) {
    return ExAllocatePoolWithTag(NonPagedPoolNx, size, MY_TAG);
}

void FreeBuffer(PVOID buffer) {
    if (buffer) {
        ExFreePoolWithTag(buffer, MY_TAG);
    }
}

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    PVOID buffer = AllocateBuffer(256);
    FreeBuffer(buffer);
    DriverObject->DriverUnload = [](PDRIVER_OBJECT) {};
    return STATUS_SUCCESS;
}
```
