// Client part for Server-Client chat. Developed by Mr_Dezz

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <inaddr.h>
#include <stdio.h>
#include <vector>

#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <windows.h>
#include <locale>
#include <codecvt>
#include <string>
#include <random>
using namespace std;


#include <thread> // Для std::this_thread::sleep_for
#include <chrono> // Для std::chrono::milliseconds

#pragma comment(lib, "ws2_32.lib")

using namespace std;

vector<wstring> eng_v;
vector<wstring> rus_v;
vector<int> num;
SOCKET ClientSock;

void Link()
{
	//const char SERVER_IP[] = "192.168.0.11/24";			// Enter local Server IP address
	//const char SERVER_IP[] = "89.223.124.180/24";			//x-treame.com Artem server
	const char SERVER_IP[] = "176.109.110.38/24";			//cloud.ru
	
	const short SERVER_PORT_NUM = 1235;				// Enter Listening port on Server side
	const short BUFF_SIZE = 1024;					// Maximum size of buffer for exchange info between server and client

	// Key variables for all program
	int erStat;										// For checking errors in sockets functions

	//IP in string format to numeric format for socket functions. Data is in "ip_to_num"
	in_addr ip_to_num;
	inet_pton(AF_INET, SERVER_IP, &ip_to_num);


	// WinSock initialization
	WSADATA wsData;
	erStat = WSAStartup(MAKEWORD(2, 2), &wsData);

	if (erStat != 0) {
		cout << "Error WinSock version initializaion #";
		cout << WSAGetLastError();
		return;
	}
	else
		cout << "WinSock initialization is OK" << endl;

	// Socket initialization
	SOCKET ClientSock = socket(AF_INET, SOCK_STREAM, 0);

	if (ClientSock == INVALID_SOCKET) {
		cout << "Error initialization socket # " << WSAGetLastError() << endl;
		closesocket(ClientSock);
		WSACleanup();
	}
	else
		cout << "Client socket initialization is OK" << endl;

	// Establishing a connection to Server
	sockaddr_in servInfo;

	ZeroMemory(&servInfo, sizeof(servInfo));

	servInfo.sin_family = AF_INET;
	servInfo.sin_addr = ip_to_num;
	servInfo.sin_port = htons(SERVER_PORT_NUM);

	erStat = connect(ClientSock, (sockaddr*)&servInfo, sizeof(servInfo));

	if (erStat != 0) {
		cout << "Connection to Server is FAILED. Error # " << WSAGetLastError() << endl;
		closesocket(ClientSock);
		WSACleanup();
		return;
	}
	else
		cout << "Connection established SUCCESSFULLY. Ready to send a message to Server" << endl;








	////Exchange text data between Server and Client. Disconnection if a Client send "xxx"

	//vector <char> servBuff(BUFF_SIZE), clientBuff(BUFF_SIZE);							// Buffers for sending and receiving data
	//short packet_size = 0;												// The size of sending / receiving packet in bytes


	//const int size = 1024;
	//char buf[size];
	//string s, s2;
	//wstring s3;
	//cin.imbue(locale(".UTF8"));
	//wcin.imbue(locale("rus_rus.866"));


	//fstream g("tmp.txt", ios::out);

	//bool is_English = 1;

	//for (int k = 0; 1;)
	//{
	//	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	//	packet_size = recv(ClientSock, buf, size, 0);
	//	/*	g << buf << endl;
	//		for (int i = 0; buf[i] != '\0'; i++)
	//		{
	//			g << buf[i] - 0 << " ";
	//		}
	//		g  << endl;*/

	//	if (packet_size == SOCKET_ERROR) {
	//		cout << "Can't receive message from Server. Error # " << WSAGetLastError() << endl;
	//		closesocket(ClientSock);
	//		WSACleanup();
	//		return;
	//	}
	//	else
	//	{

	//		for (int i = 0; buf[i] != '\0'; i++)
	//		{
	//			if (buf[i] == '\r')
	//			{
	//				buf[i] = '\0';
	//			}
	//		}

	//		cout << buf << endl;
	//		/*for (int i = 0; buf[i] != '\0'; i++)
	//		{
	//			cout << buf[i] + 0 << " ";
	//		}*/
	//		if (strcmp(buf, "f.eof") == 0)
	//			break;
	//		//cout << "Server message: " << buf << endl;

	//		int len = MultiByteToWideChar(CP_UTF8, 0, buf, -1, NULL, 0);
	//		std::wstring ws(len, 0);
	//		MultiByteToWideChar(CP_UTF8, 0, buf, -1, &ws[0], len);
	//		ws.pop_back();


	//		if (is_English)
	//		{
	//			num.push_back(k++);
	//			eng_v.push_back(ws);
	//			is_English = 0;
	//		}
	//		else
	//		{
	//			rus_v.push_back(ws);
	//			is_English = 1;
	//		}

	//		memset(buf, 0, sizeof(buf));
	//	}
	//}

	///*for (int i = 0; i < eng_v.size(); i++)
	//{
	//	wcout << eng_v[i] << " " << rus_v[i] << endl;
	//}*/


	//closesocket(ClientSock);
	//WSACleanup();
	//cout << "The connection was closed." << endl;

}


//
//void Link()
//{
//	//const char SERVER_IP[] = "192.168.0.11/24";			// Enter local Server IP address
//	const char SERVER_IP[] = "89.223.124.180/24";
//
//	const short SERVER_PORT_NUM = 1235;				// Enter Listening port on Server side
//	const short BUFF_SIZE = 1024;					// Maximum size of buffer for exchange info between server and client
//
//	// Key variables for all program
//	int erStat;										// For checking errors in sockets functions
//
//	//IP in string format to numeric format for socket functions. Data is in "ip_to_num"
//	in_addr ip_to_num;
//	inet_pton(AF_INET, SERVER_IP, &ip_to_num);
//
//
//	// WinSock initialization
//	WSADATA wsData;
//	erStat = WSAStartup(MAKEWORD(2, 2), &wsData);
//
//	if (erStat != 0) {
//		cout << "Error WinSock version initializaion #";
//		cout << WSAGetLastError();
//		return;
//	}
//	else
//		cout << "WinSock initialization is OK" << endl;
//
//	// Socket initialization
//	SOCKET ClientSock = socket(AF_INET, SOCK_STREAM, 0);
//
//	if (ClientSock == INVALID_SOCKET) {
//		cout << "Error initialization socket # " << WSAGetLastError() << endl;
//		closesocket(ClientSock);
//		WSACleanup();
//	}
//	else
//		cout << "Client socket initialization is OK" << endl;
//
//	// Establishing a connection to Server
//	sockaddr_in servInfo;
//
//	ZeroMemory(&servInfo, sizeof(servInfo));
//
//	servInfo.sin_family = AF_INET;
//	servInfo.sin_addr = ip_to_num;
//	servInfo.sin_port = htons(SERVER_PORT_NUM);
//
//	erStat = connect(ClientSock, (sockaddr*)&servInfo, sizeof(servInfo));
//
//	if (erStat != 0) {
//		cout << "Connection to Server is FAILED. Error # " << WSAGetLastError() << endl;
//		closesocket(ClientSock);
//		WSACleanup();
//		return;
//	}
//	else
//		cout << "Connection established SUCCESSFULLY. Ready to send a message to Server" << endl;
//
//
//	//Exchange text data between Server and Client. Disconnection if a Client send "xxx"
//
//	vector <char> servBuff(BUFF_SIZE), clientBuff(BUFF_SIZE);							// Buffers for sending and receiving data
//	short packet_size = 0;												// The size of sending / receiving packet in bytes
//
//	
//	const int size = 1024;
//	char buf[size];
//	string s, s2;
//	wstring s3;
//	cin.imbue(locale(".UTF8"));
//	wcin.imbue(locale("rus_rus.866"));
//
//
//	fstream g("tmp.txt", ios::out);
//
//	bool is_English = 1;
//
//	for (int k = 0; 1;)
//	{
//		std::this_thread::sleep_for(std::chrono::milliseconds(10));
//
//		packet_size = recv(ClientSock, buf, size, 0);
//	/*	g << buf << endl;
//		for (int i = 0; buf[i] != '\0'; i++)
//		{
//			g << buf[i] - 0 << " ";
//		}
//		g  << endl;*/
//
//		if (packet_size == SOCKET_ERROR) {
//			cout << "Can't receive message from Server. Error # " << WSAGetLastError() << endl;
//			closesocket(ClientSock);
//			WSACleanup();
//			return;
//		}
//		else
//		{
//
//			for (int i = 0; buf[i] != '\0'; i++)
//			{
//				if (buf[i] == '\r')
//				{
//					buf[i] = '\0';
//				}
//			}
//
//			cout << buf << endl;
//			/*for (int i = 0; buf[i] != '\0'; i++)
//			{
//				cout << buf[i] + 0 << " ";
//			}*/
//			if (strcmp(buf, "f.eof") == 0)
//				break;
//			//cout << "Server message: " << buf << endl;
//
//			int len = MultiByteToWideChar(CP_UTF8, 0, buf, -1, NULL, 0);
//			std::wstring ws(len, 0);
//			MultiByteToWideChar(CP_UTF8, 0, buf, -1, &ws[0], len);
//			ws.pop_back();
//
//
//			if (is_English)
//			{
//				num.push_back(k++);
//				eng_v.push_back(ws);
//				is_English = 0;
//			}
//			else
//			{
//				rus_v.push_back(ws);
//				is_English = 1;
//			}
//
//			memset(buf, 0, sizeof(buf));
//		}
//	}
//
//	/*for (int i = 0; i < eng_v.size(); i++)
//	{
//		wcout << eng_v[i] << " " << rus_v[i] << endl;
//	}*/
//
//
//	closesocket(ClientSock);
//	WSACleanup();
//	cout << "The connection was closed." << endl;
//
//}


int main(void)
{
	setlocale(LC_ALL, ".UTF8");
	//Key constants
	//const char SERVER_IP[] = "89.223.124.180/24";			// Enter local Server IP address

	Link();

	int t;
	bool k = true;
	float score = 0;
	srand(time(0));

	wstring s;
	shuffle(num.begin(), num.end(), std::default_random_engine(std::time(0)));

	for (int i = 0; i < num.size(); i++)
	{
		if (k)
		{
			t = num[i];
		}

		if (rand() % 2 == 0)
		{
			do
			{
				wcout << eng_v[t] << L" - ";

				getline(wcin, s);
				for (int i = s.size() - 1; i >= 0; i--)
				{
					if (s[i] == ' ')
					{
						s.pop_back();
					}
					else
						break;
				}
				if (s == rus_v[t])
				{
					k = true;
					wcout << L"правильно, следующее" << endl;
					score++;
				}
				else
				{
					if (k)
					{
						score--;
					}
					wcout << L"не верно, правильный ответ - " << rus_v[t] << endl;
					k = false;
				}
			} while (!k);
		}
		else
		{
			do
			{
				wcout << rus_v[t] << L" - ";

				getline(wcin, s);
				for (int i = s.size() - 1; i >= 0; i--)
				{
					if (s[i] == ' ')
					{
						s.pop_back();
					}
					else
						break;
				}
				if (s == eng_v[t])
				{
					k = true;
					wcout << L"правильно, следующее" << endl;
					score++;
				}
				else
				{
					if (k)
					{
						score--;
					}
					wcout << L"не верно, правильный ответ - " << eng_v[t] << endl;
					k = false;
				}
			} while (!k);

		}

	}
	wcout << L"Количество проавильных ответов - " << score << L" из " << num.size() << L" это " << score * 100 / num.size() << L"%" << endl;

	return 0;

}