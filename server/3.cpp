#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <fstream>
#include <codecvt>

using namespace std;

int main()
{
    // create
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        cerr << "can't create a socket";
        return 1;
    }
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(1235);
    // inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr);
    inet_pton(AF_INET, "89.223.124.180/24", &hint.sin_addr);

    if (bind(listening, (struct sockaddr *)&hint, sizeof(hint)) == -1)
    {
        cerr << "can't bind to ip/port";
        return -2;
    }

    // if(bind(listening,AF_INET, (struct sockaddr *)&hint, sizeof(hint)) == -1)
    // {
    //     cerr<<"can't bind to ip/port";
    //    return -2;
    //}

    ///////

    std::cout << "listen" << std::endl;

    if (listen(listening, SOMAXCONN) == 1)
    {
        cerr << "can't listen";
        return -3;
    }

    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

    const int size = 1024;

    locale::global(locale(""));


    char buf[size];

    fstream g("tmp.txt",ios::out);

    while (1)
    {
        std::cout << "new connection" << std::endl;

        int clientSocket = accept(listening, (struct sockaddr *)&client, &clientSize);

        if (clientSocket == -1)
        {
            cerr << "Problem with client connecting";
            return -4;
        }

        fstream f("eng.txt", ios::in);
        fstream f2("rus.txt", ios::in);
        const int size = 1024;


        switch (fork())
        {
        case -1:
            perror("fork");
            break;
        case 0:
          //   close(listening);

            for (;;)
            {

                f.getline(buf,size);
                  if (f.eof())
                    break;
                send(clientSocket, buf, size, 0);
                f2.getline(buf,size);

                send(clientSocket, buf, size, 0);

            }
            strcpy(buf, "f.eof");
            send(clientSocket, buf, size, 0);
            close(clientSocket); // закрываем сокет
            f.close();
            f2.close();
	    cout<<"connection complited"<<endl;
            exit(0);
        default:
            close(clientSocket);
        }
    }







    ////////////////////////


    /*
    close(listening);

    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);

    int result = getnameinfo((struct sockaddr *)&client, sizeof(client), host,
                             NI_MAXHOST, svc, NI_MAXSERV, 0);

    if (result)
    {
        cout << host << " connected on service" << endl;
        // cout<<host<<" connected on "<<service<<endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << "connected on" << ntohs(client.sin_port) << endl;
    }
    short packet_size = 0;
    const int size = 1024;

    locale::global(locale(""));

    // char buf[size];
    char cl_buf[size];

    char buf[size];

    fstream f("1.txt", ios::in);

    // uint32_t len= htonl(utf8String.size())

    while (1)
    {
        sock = accept(listener, hint, NULL); // принимаем входные подключение и создаем отделный сокет для каждого нового подключившегося клиента
        if (sock < 0)
        {
            perror("Прием входящих подключений");
            exit(3);
        }

        switch (fork())
        {
        case -1:
            perror("fork");
            break;
        case 0:
            close(listener);

            for (;;)
            {
                // f.getline(buf,size);
                f >> buf;
                if (f.eof())
                    break;
                cout << buf << endl;

                packet_size = send(clientSocket, buf, size, 0);
            }
            strcpy(buf, "f.eof");
            packet_size = send(clientSocket, buf, size, 0);
            close(sock); // закрываем сокет
            exit(0);
        default:
            close(sock);
        }
    }

    close(clientSocket);*/
}




/*
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int sock, listener;      // дескрипторы сокетов
    struct sockaddr_in addr; // структура с адресом
    char buf[2048];          // буфур для приема
    int bytes_read;          // кол-во принятых байт

    listener = socket(AF_INET, SOCK_STREAM, 0); // создаем сокет для входных подключений
    if (listener < 0)
    {
        perror("socket");
        exit(1);
    }

    // Указываем параметры сервера
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1235);
    // addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_addr.s_addr = inet_addr("192.168.0.11");
    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0) // связываемся с сетевым устройство. Сейчас это устройство lo - "петля", которое используется для отладки сетевых приложений
    {
        perror("bind");
        exit(2);
    }
    std::cout << "listen" << std::endl;

    listen(listener, 1); // очередь входных подключений

    std::cout << "after listen" << std::endl;

    while (1)
    {
        sock = accept(listener, (struct sockaddr *)&addr, NULL); // принимаем входные подключение и создаем отделный сокет для каждого нового подключившегося клиента
        if (sock < 0)
        {
            perror("Прием входящих подключений");
            exit(3);
        }
        fstream f("1.txt", ios::in);
        const int size = 1024;

        char cl_buf[size];

        switch (fork())
        {
        case -1:
            perror("fork");
            break;
        case 0:
            close(listener);

            for (;;)
            {

                // f.getline(buf,size);
                f >> buf;
                if (f.eof())
                    break;
                cout << buf << endl;

                send(sock, buf, size, 0);
            }
            strcpy(buf, "f.eof");
            send(sock, buf, size, 0);
            close(sock); // закрываем сокет

            exit(0);
        default:
            close(sock);
        }
    }

    return 0;
}
*/
