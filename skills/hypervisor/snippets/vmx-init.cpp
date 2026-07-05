# VMX Initialization Snippet

```cpp
#include <intrin.h>
#include <stdint.h>

bool EnableVMX() {
    uint64_t ia32_feature_control = __readmsr(0x3A);
    if (!(ia32_feature_control & (1ULL << 2))) {
        return false;
    }

    // Allocate and align VMXON region to 4KB
    void* vmxon = _aligned_malloc(4096, 4096);
    if (!vmxon) return false;

    uint64_t vmx_revision = __readmsr(0x48);
    *reinterpret_cast<uint32_t*>(vmxon) = static_cast<uint32_t>(vmx_revision);

    uint64_t rflags = __vmx_on(reinterpret_cast<uint64_t>(vmxon));
    return (rflags & 0x1) == 0;
}
```
