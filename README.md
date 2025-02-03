# Reverse Shell (Windows)   [for Educational Purposes Only]

This project demonstrates the creation of a reverse shell using Windows sockets and the Windows API. It connects to a remote server and executes commands sent from the server by spawning a command prompt (`cmd.exe`) process on the target machine.

![image](https://github.com/user-attachments/assets/52b4ec05-2071-4833-97af-c25d2593b83e)



![image](https://github.com/user-attachments/assets/9f4b58c8-8883-43cb-8fa7-1157d170c1b8)

## Features:
- Establishes a reverse shell connection from a vulnerable machine to a remote server.
- Uses Winsock for socket communication.
- Spawns `cmd.exe` on the target machine to execute commands remotely.
- Redirects input, output, and error streams to and from the socket.

## Files:
- `reverseShell.c`: The source code that implements the reverse shell.

## Dependencies:
- **Winsock 2.2** (WS2_32.lib): Used for socket communication.
- **Windows API**: Used for spawning processes (`CreateProcess`), managing handles (`STARTUPINFO`), and redirecting I/O.

## How to Compile:
To compile the `reverseShell.c` file using Microsoft's **Visual Studio Developer Command Prompt** or **cl.exe**:

```bash
cl reverseShell.c /link Ws2_32.lib
