#include <iostream>
#include <windows.h>

int main() {
    // Create a heap
    HANDLE hHeap = HeapCreate(0, 0, 0);
    if (hHeap == NULL) {
        std::cerr << "HeapCreate failed with error: " << GetLastError() << std::endl;
        return 1;
    }

    // Allocate 50 bytes of memory on the heap
    SIZE_T totalSize = 50;
    void* pMemory = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, totalSize);
    if (pMemory == NULL) {
        std::cerr << "HeapAlloc failed with error: " << GetLastError() << std::endl;
        HeapDestroy(hHeap);
        return 1;
    }

    // Divide the 50-byte block into two pointers
    void* pBlock1 = pMemory;                          // First 20 bytes
    void* pBlock2 = static_cast<unsigned char*>(pMemory) + 20; // Remaining 30 bytes

    // Use the allocated memory
    std::cout << "Memory allocated at address: " << pMemory << std::endl;
    std::cout << "Block 1 address: " << pBlock1 << std::endl;
    std::cout << "Block 2 address: " << pBlock2 << std::endl;

    // In practice, you would use the blocks here. This is just a placeholder.

    // Free the entire block of memory
    if (!HeapFree(hHeap, 0, pMemory)) {
        std::cerr << "HeapFree failed with error: " << GetLastError() << std::endl;
        HeapDestroy(hHeap);
        return 1;
    }

    // Destroy the heap
    if (!HeapDestroy(hHeap)) {
        std::cerr << "HeapDestroy failed with error: " << GetLastError() << std::endl;
        return 1;
    }

    return 0;
}
