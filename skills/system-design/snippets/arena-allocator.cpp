#include <cstddef>
#include <cstdint>
#include <iostream>

class ArenaAllocator {
public:
    ArenaAllocator(size_t size)
        : size_(size), buffer_(new uint8_t[size]), offset_(0) {}

    ~ArenaAllocator() {
        delete[] buffer_;
    }

    void* Allocate(size_t size, size_t alignment = alignof(std::max_align_t)) {
        size_t aligned = (offset_ + alignment - 1) & ~(alignment - 1);
        if (aligned + size > size_) {
            return nullptr;
        }
        void* ptr = buffer_ + aligned;
        offset_ = aligned + size;
        return ptr;
    }

    void Reset() {
        offset_ = 0;
    }

private:
    size_t size_;
    uint8_t* buffer_;
    size_t offset_;
};

int main() {
    ArenaAllocator arena(1024);
    int* value = static_cast<int*>(arena.Allocate(sizeof(int)));
    if (value) {
        *value = 42;
        std::cout << "Allocated: " << *value << "\n";
    }
    arena.Reset();
    return 0;
}
