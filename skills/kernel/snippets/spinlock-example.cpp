# Kernel Spin Lock Snippet

```cpp
#include <ntddk.h>

KSPIN_LOCK gLock;

VOID ExampleRoutine() {
    KIRQL oldIrql;
    KeAcquireSpinLock(&gLock, &oldIrql);
    // Critical section at DISPATCH_LEVEL
    // Protected shared state here
    KeReleaseSpinLock(&gLock, oldIrql);
}

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    KeInitializeSpinLock(&gLock);
    DriverObject->DriverUnload = [](PDRIVER_OBJECT) {};
    return STATUS_SUCCESS;
}
```
