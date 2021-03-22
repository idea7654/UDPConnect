#include <iostream>
#include <stdio.h>
#include <WinSock2.h>
//gcc -o IOCP_Server.exe IOCP_Server.cpp -lws2_32 -lstdc++

#pragma comment(lib, "ws2_32.lib");

#define PORT_NUM 9000

using namespace std;

int main(void){
    WSADATA wsaData;
    SOCKET listenSocket;
    SOCKADDR_IN servAddr;
    char myaddr[] = "127.0.0.1";

    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR){
        printf("Failed WSAStratup() \n");
        return 1;
    }
    listenSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(listenSocket == -1){
        cout << "Failed createSocket" << endl;
        return 1;
    }

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    // servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_addr.s_addr = inet_addr(myaddr);
    servAddr.sin_port = htons(PORT_NUM);

    if(bind(listenSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == -1){
        cout << "Binding Error" << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    cout << "Start server!";

    char buffer[1024];
    char recvByte;
    int recvCount = 0;
    SOCKET clientSocket;
    SOCKADDR_IN clientAddr;
    int clientAddrlen = sizeof(clientAddr);
    while(1){
        memset(&buffer, 0, sizeof(buffer));
        recvByte = recvfrom(clientSocket, (char*)&buffer, sizeof(buffer), 0, (SOCKADDR*)&clientAddr, &clientAddrlen);
        cout << 1 << endl;
        if(recvByte > 1){
            cout << "데이터 받음!" << endl;
            break;
        }
    }

    closesocket(listenSocket);
    WSACleanup();

    return 0;
}