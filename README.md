This exemple of send image by TCP use linux native sockets

This project for Visual studio and WSL

Custom settings for client and server projects:
General -> Platform Toolset = GCC for Windows Subsystem for Linux,
C/C++ -> All Options = C++ Language Standard = C++17 (-std=c++17),
Linker -> Command Line-> Additional Options = -pthread;

Set your own port, ip and file path in Configuration classes in client and server projects
