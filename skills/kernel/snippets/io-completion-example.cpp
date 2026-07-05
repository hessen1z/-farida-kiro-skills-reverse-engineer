# Kernel I/O Completion Snippet

```cpp
#include <ntddk.h>

void CompleteIrp(PIRP Irp, NTSTATUS status, ULONG_PTR info) {
    Irp->IoStatus.Status = status;
    Irp->IoStatus.Information = info;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
}

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    DriverObject->MajorFunction[IRP_MJ_READ] = [](PDEVICE_OBJECT DeviceObject, PIRP Irp) {
        UNREFERENCED_PARAMETER(DeviceObject);
        CompleteIrp(Irp, STATUS_SUCCESS, 0);
        return STATUS_SUCCESS;
    };
    DriverObject->DriverUnload = [](PDRIVER_OBJECT) {};
    return STATUS_SUCCESS;
}
```
