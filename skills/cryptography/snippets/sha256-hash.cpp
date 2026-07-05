#include <windows.h>
#include <bcrypt.h>
#include <cstdio>

#pragma comment(lib, "Bcrypt.lib")

int main() {
    BCRYPT_ALG_HANDLE algHandle = nullptr;
    if (BCryptOpenAlgorithmProvider(&algHandle, BCRYPT_SHA256_ALGORITHM, nullptr, 0) != 0) {
        printf("Open algorithm provider failed\n");
        return 1;
    }

    BCRYPT_HASH_HANDLE hashHandle = nullptr;
    DWORD hashObjectSize = 0;
    DWORD dataSize = 0;
    BCryptGetProperty(algHandle, BCRYPT_OBJECT_LENGTH, (PUCHAR)&hashObjectSize, sizeof(DWORD), &dataSize, 0);
    BYTE* hashObject = new BYTE[hashObjectSize];

    if (BCryptCreateHash(algHandle, &hashHandle, hashObject, hashObjectSize, nullptr, 0, 0) != 0) {
        printf("Create hash failed\n");
        delete[] hashObject;
        BCryptCloseAlgorithmProvider(algHandle, 0);
        return 1;
    }

    const BYTE message[] = "message";
    if (BCryptHashData(hashHandle, (PUCHAR)message, sizeof(message) - 1, 0) != 0) {
        printf("Hash data failed\n");
        BCryptDestroyHash(hashHandle);
        delete[] hashObject;
        BCryptCloseAlgorithmProvider(algHandle, 0);
        return 1;
    }

    BYTE hash[32] = {0};
    if (BCryptFinishHash(hashHandle, hash, sizeof(hash), 0) != 0) {
        printf("Finish hash failed\n");
        BCryptDestroyHash(hashHandle);
        delete[] hashObject;
        BCryptCloseAlgorithmProvider(algHandle, 0);
        return 1;
    }

    printf("SHA-256 hash generated\n");
    BCryptDestroyHash(hashHandle);
    delete[] hashObject;
    BCryptCloseAlgorithmProvider(algHandle, 0);
    return 0;
}
