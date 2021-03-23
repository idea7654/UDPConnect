#include <stdio.h>
#include <iostream>
#include <winsock2.h> // 윈속 헤더 포함 
#include <thread>
#pragma comment (lib,"ws2_32.lib") // 윈속 라이브러리 링크
#define BUFFER_SIZE 1024 // 버퍼 사이즈

using namespace std;

void useSocket(){
    WSADATA wsaData; // 윈속 데이터 구조체.(WSAStartup() 사용할꺼!)
    SOCKET ServerSocket; // 소켓 선언
    SOCKADDR_IN ServerInfo; // 서버 주소정보 구조체
    SOCKADDR_IN FromClient; // 클라이언트에서 받는 주소정보 구조체
 
    int FromClient_Size; // 클라이언트로부터 받는 메시지 크기
    int Recv_Size; // 받는 사이즈
    int Send_Size; // 보내는 사이즈
    int Count;
 
    char Buffer[ BUFFER_SIZE ];
    short ServerPort = 9000; // 서버 포트번호
 
    //WSAStartup은 WS2_32.DLL을 초기화 하는 함수
    if( WSAStartup(0x202,&wsaData) == SOCKET_ERROR ) // WSAStartup 설정에서 문제 발생하면
    {
        cout<<"WinSock error "<<endl;
        WSACleanup(); // WS2_32.DLL의 사용 끝냄
    }
 
    // memset : 사용자가 정한 메모리 크기만큼 메모리 영역을 특정한 값으로 채움
    memset( &ServerInfo, 0, sizeof(ServerInfo) ); // 0으로 초기화
    memset( &FromClient, 0, sizeof(FromClient) );
    memset( Buffer, 0, BUFFER_SIZE );
 
    ServerInfo.sin_family  = AF_INET; // IPv4 주소체계 사용 
    ServerInfo.sin_addr.s_addr = inet_addr( "127.0.0.1" ); // 루프백 IP. 즉 혼자놀이용..
    ServerInfo.sin_port   = htons( ServerPort ); // 포트번호
 
    // 소켓 생성
    ServerSocket = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP ); // udp용 소켓 생성. SOCK_DGRAM : UDP 사용
    if( ServerSocket == INVALID_SOCKET ) // 에러 발생시
    {
        cout<<"cant make socket."<<endl;
        closesocket( ServerSocket );
        WSACleanup();
        exit(0);
    }
 
    // bind() - 새로 오는 클라이언트를 받을 welcome 소켓
    // 전달만 할꺼면 필요없음
    if( ::bind( ServerSocket, (sockaddr*)&ServerInfo, sizeof(ServerInfo) ) == SOCKET_ERROR )
    {
        cout<<"cannot bind."<<endl;
        closesocket( ServerSocket );
        WSACleanup();
        exit(0);
    }
 
    while(1)
    {
        FromClient_Size = sizeof( FromClient );
        // recvfrom : UDP통신 비연결형.  패킷수신
        Recv_Size = recvfrom( ServerSocket, Buffer, BUFFER_SIZE, 0,
            (struct sockaddr*) &FromClient, &FromClient_Size );
 
        if( Recv_Size < 0 )
        { 
            cout<<"recvfrom() error!"<<endl; 
            exit(0); 
        }
 
        cout<<"packet recv! client is "<<inet_ntoa( FromClient.sin_addr )<< endl;
        cout<<"packet data is " <<Buffer << endl;
 
        //패킷송신
        Send_Size = sendto( ServerSocket, Buffer, Recv_Size, 0,
            (struct sockaddr*) &FromClient, sizeof( FromClient ) );
        if( Send_Size != Recv_Size )
        { 
            cout<<"sendto() error!" <<endl;
            exit(0); 
        }else{
            break;
        }
    }
    closesocket( ServerSocket ); // 소켓을 닫습니다.
    WSACleanup();
}
void countNum(){
    cout << "1234" << endl;
}
int main(void)
{
    thread th1(useSocket);
    thread th2(countNum);

    th1.join();
    th2.join();

    return 0;
}