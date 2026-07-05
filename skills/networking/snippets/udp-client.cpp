#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstdio>

#pragma comment(lib, "Ws2_32.lib")

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    SOCKET sendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sendSocket == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    sockaddr_in service{};
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(27016);

    const char* message = "Hello UDP";
    int result = sendto(sendSocket, message, (int)strlen(message), 0,
                        (sockaddr*)&service, sizeof(service));
    if (result == SOCKET_ERROR) {
        printf("sendto failed: %d\n", WSAGetLastError());
    } else {
        printf("Sent %d bytes\n", result);
    }

    closesocket(sendSocket);
    WSACleanup();
    return 0;
}
