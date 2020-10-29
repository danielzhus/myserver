#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
 
#define SERVER_PORT 8888
 
int main(int argc, char* argv[]) 
{
    if (argc != 2)
    {
        printf("./client fileName");
    }
    //客户端只需要一个套接字文件描述符，用于和服务器通信
    int clientSocket;
 
    //描述服务器的socket
    struct sockaddr_in serverAddr;
    char sendbuf[200] = {0};
    char recvbuf[200] = {0};
    int iDataNum;
 
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return 1;
    }
 
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
 
    //指定服务器端的ip，本地测试：127.0.0.1
    //inet_addr()函数，将点分十进制IP转换成网络字节序IP
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        perror("connect");
        return 1;
    }
    printf("连接到主机...\n");

    // 读取文件请求
    FILE* reqFile = fopen(argv[1], "r");
    fread(sendbuf, 1024, 1, reqFile);
    if (strlen(sendbuf) == 0)
    {
        printf("文件读取失败\n");
        fclose(reqFile);
        close(clientSocket);
        return -1;
    }
    fclose(reqFile);

    printf("发送消息:");
    printf("\n");
    send(clientSocket, sendbuf, strlen(sendbuf), 0);

    printf("读取消息:");
    recvbuf[0] = '\0';
    iDataNum = recv(clientSocket, recvbuf, 200, 0);
    recvbuf[iDataNum] = '\0';
    printf("%s\n", recvbuf);
 
    close(clientSocket);
    return 0;
 
}
