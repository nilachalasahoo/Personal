#include <iostream>
#include <windows.h>

int main() {
    // Allocate 50 bytes of memory
    SIZE_T size = 50;
    void* pMemory = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (pMemory == NULL) {
        std::cerr << "VirtualAlloc failed with error: " << GetLastError() << std::endl;
        return 1;
    }

    // Divide the 50-byte block into two parts
    void* pBlock1 = pMemory;                          // First 20 bytes
    void* pBlock2 = static_cast<unsigned char*>(pMemory) + 20; // Remaining 30 bytes

    // Use the allocated memory
    std::cout << "Memory allocated at address: " << pMemory << std::endl;
    std::cout << "Block 1 address: " << pBlock1 << std::endl;
    std::cout << "Block 2 address: " << pBlock2 << std::endl;

    // Deallocate the entire block of memory
    if (!VirtualFree(pMemory, 0, MEM_RELEASE)) {
        std::cerr << "VirtualFree failed with error: " << GetLastError() << std::endl;
        return 1;
    }

    return 0;
}
