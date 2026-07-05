#include <windows.h>
#include <bcrypt.h>
#include <cstdio>

#pragma comment(lib, "Bcrypt.lib")

int main() {
    BCRYPT_ALG_HANDLE algHandle = nullptr;
    if (BCryptOpenAlgorithmProvider(&algHandle, BCRYPT_AES_ALGORITHM, nullptr, 0) != 0) {
        printf("BCryptOpenAlgorithmProvider failed\n");
        return 1;
    }

    if (BCryptSetProperty(algHandle, BCRYPT_CHAINING_MODE, (PUCHAR)BCRYPT_CHAIN_MODE_GCM, sizeof(BCRYPT_CHAIN_MODE_GCM), 0) != 0) {
        printf("Failed to set chaining mode\n");
        BCryptCloseAlgorithmProvider(algHandle, 0);
        return 1;
    }

    BCRYPT_KEY_HANDLE keyHandle;
    BYTE key[16] = {0};
    if (BCryptGenerateSymmetricKey(algHandle, &keyHandle, nullptr, 0, key, sizeof(key), 0) != 0) {
        printf("Failed to generate key\n");
        BCryptCloseAlgorithmProvider(algHandle, 0);
        return 1;
    }

    BYTE iv[12] = {0};
    BYTE plaintext[] = "example plaintext";
    BYTE ciphertext[128] = {0};
    BYTE tag[16] = {0};
    BCRYPT_AUTHENTICATED_CIPHER_MODE_INFO authInfo;
    BCRYPT_INIT_AUTH_MODE_INFO(authInfo);
    authInfo.pbNonce = iv;
    authInfo.cbNonce = sizeof(iv);
    authInfo.pbTag = tag;
    authInfo.cbTag = sizeof(tag);

    ULONG resultLength;
    if (BCryptEncrypt(keyHandle, plaintext, sizeof(plaintext) - 1,
                     &authInfo, nullptr, 0, ciphertext, sizeof(ciphertext), &resultLength, 0) != 0) {
        printf("Encryption failed\n");
        BCryptDestroyKey(keyHandle);
        BCryptCloseAlgorithmProvider(algHandle, 0);
        return 1;
    }

    printf("Encrypted %lu bytes\n", resultLength);

    BCryptDestroyKey(keyHandle);
    BCryptCloseAlgorithmProvider(algHandle, 0);
    return 0;
}
