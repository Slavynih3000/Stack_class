#include <iostream>
//#include "stdafx.h" // надо скомпиллировать отдельно и указать заголоки нужные компилятору
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <windows.h>
#pragma comment(lib, "user32.lib") 
#pragma warning(disable: 4996)
int main() {
	WSAData Data;
	WORD Version = MAKEWORD(2, 1);
	if (WSAStartup(Version, &Data) != 0) {
		std::cout << "Error";
		return 0;
	}
	SOCKADDR_IN addres;
	addres.sin_addr.s_addr = inet_addr("127.0.0.1");
	addres.sin_port = htons(1025);
	addres.sin_family = AF_INET;

	int k = sizeof(addres);
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, NULL);
	bind(slisten, (SOCKADDR*)&addres, sizeof(addres));

	listen(slisten, SOMAXCONN);//2 праметр количество ожидания запросов
	SOCKET Connect;
	Connect = accept(slisten, (SOCKADDR*)&addres, &k);
	
	if (Connect == 0) {
		std::cout << "NO CONNECTION";
	}
	else std::cout << "CONNECTION";
	system("pause");
	return 1;
}