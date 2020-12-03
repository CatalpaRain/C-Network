/*UDP服务端*/
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
		cout << "WinSock启动失败";
		return 0;
	}
	/*创建一个监听套接字监听客户端的发送信息状态*/
	SOCKET slisten = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	/*套接字绑定到结构体sokcaddr_in。*/
	if (bind(slisten, (SOCKADDR *)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		cout << "bind socket错误" << endl;
		system("pause");
		return 0;
	}
	//指向存有源地址的相关信息的缓冲区
	sockaddr_in remoteddr;
	int nlen = sizeof(remoteddr);
	/*进入循环监听状态。*/
	while (true)
	{
		char recdata[255];
		int ret = recvfrom(slisten, recdata, 255, 0, (SOCKADDR *)&remoteddr, &nlen);
		if (ret > 0)
		{
			recdata[ret] = 0x00;
			printf("收到来自IP地址：%s 的数据:\n%s", inet_ntoa(remoteddr.sin_addr), recdata);
		}
	}
	/*关闭套接字和WSA库*/
	closesocket(slisten);
	WSACleanup();
	system("pause");
	return 0;
}