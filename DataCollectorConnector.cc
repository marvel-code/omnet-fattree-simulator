/*
 * DataCollectorConnector.cpp
 *
 *  Created on: Apr 8, 2022
 *      Author: user
 */

#include "DataCollectorConnector.h"
#include <stdio.h>
#include <winsock2.h>

DataCollectorConnector::DataCollectorConnector() {
    WORD ver = MAKEWORD(2,2);
    WSADATA wsaData;
    int retVal=0;

    WSAStartup(ver,(LPWSADATA)&wsaData);

    LPHOSTENT hostEnt;

    hostEnt = gethostbyname("127.0.0.1");

    if(!hostEnt)
    {
        printf("Unable to collect gethostbyname\n");
        WSACleanup();
        throw 1;
    }

    //Создаем сокет
    SOCKET clientSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(clientSock == SOCKET_ERROR)
    {
        printf("Unable to create socket\n");
        WSACleanup();
        throw 2;
    }

    SOCKADDR_IN serverInfo;

    serverInfo.sin_family = PF_INET;
    serverInfo.sin_addr = *((LPIN_ADDR)*hostEnt->h_addr_list);
    serverInfo.sin_port = htons(50123);

    retVal=connect(clientSock,(LPSOCKADDR)&serverInfo, sizeof(serverInfo));
    if(retVal==SOCKET_ERROR)
    {
        printf("Unable to connect\n");
        WSACleanup();
        throw 3;
    }

    printf("Connection made sucessfully\n");

    char *pBuf = "Request";

    printf("Sending request from client\n");
    retVal = send(clientSock, pBuf, strlen(pBuf), 0);

    if(retVal == SOCKET_ERROR)
    {
        printf("Unable to send\n");
        WSACleanup();
        throw 4;
    }

    char szResponse[9];
    retVal = recv(clientSock, szResponse, 9, 0);

    if(retVal == SOCKET_ERROR)
    {
        printf("Unable to recv\n");
        WSACleanup();
        throw 5;
    }

    printf("Got the response from server\n%s\n",szResponse);

    shutdown(clientSock, SD_SEND);
    closesocket(clientSock);
    WSACleanup();
}

