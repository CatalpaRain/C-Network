/*UDP客户端*/
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)
#pragma warning(disable : 6386)
using namespace std;//提供一个全局的命名空间namespace，可以避免导致全局命名冲突问题。
int main()
{
	WORD sockVersion = MAKEWORD(2, 2);

	WSADATA wsadata;
	if (WSAStartup(sockVersion, &wsadata) != 0)
	{
		printf("WinSock2 initalise failed!");
		return 0;
	}

	/*创建套接字，设置相关参数，本地ip地址和端口号*/
	SOCKET sClient = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in sclient;
	sclient.sin_family = AF_INET;
	sclient.sin_port = htons(8888);
	sclient.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int nlen = sizeof(sclient);

	cout << "客户端\n输入要发送的数据" << endl;
	string str;
	getline(cin, str);
	const int nLen = sizeof(str);

	char sendData[nLen];
	strcpy_s(sendData, str.c_str());

	/*利用sendto()函数进行数据发送，注意参数列表代表的含义。*/
	sendto(sClient, (char *)sendData, strlen(sendData), 0, (sockaddr *)&sclient, nlen);
	closesocket(sClient);
	WSACleanup();
	system("pause");
	return 0;
}