# EPT Walk Snippet

```cpp
#include <stdint.h>

struct EPTEntry {
    uint64_t value;
};

bool IsEptReadable(const EPTEntry& entry) {
    return entry.value & 0x1;
}

bool IsEptWritable(const EPTEntry& entry) {
    return entry.value & 0x2;
}

bool IsEptExecutable(const EPTEntry& entry) {
    return entry.value & 0x4;
}
```
