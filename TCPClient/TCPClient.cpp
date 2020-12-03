#include<winsock2.h>
#include<iostream>
#include<string>
#pragma warning(disable : 4996)

using namespace std;
#pragma comment(lib, "ws2_32.lib")

int main()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}

	while (true)
	{
		SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sclient == INVALID_SOCKET)
		{
			cout << "invalid socket!" << endl;
			return 0;
		}

		sockaddr_in serAddr;
		serAddr.sin_family = AF_INET;
		serAddr.sin_port = htons(8888);
		serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		if (connect(sclient, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		{
			//连接失败 
			cout << "connect error !" << endl;
			closesocket(sclient);
			return 0;
		}

		string data;
		cin >> data;
		const char* sendData;
		sendData = data.c_str();   //string转const char* 

		/*
		send()用来将数据由指定的socket传给对方主机
		int send(int s, const void * msg, int len, unsigned int flags)
			s为已建立好连接的socket，msg指向数据内容，len则为数据长度，参数flags一般设0
			成功则返回实际传送出去的字符数，失败返回-1，错误原因存于error
		*/
		send(sclient, sendData, strlen(sendData), 0);

		char recData[255];
		int ret = recv(sclient, recData, 255, 0);
		if (ret > 0)
		{
			recData[ret] = 0x00;
			cout << recData << endl;
		}
		closesocket(sclient);
	}

	WSACleanup();

	system("pause");
	return 0;
}