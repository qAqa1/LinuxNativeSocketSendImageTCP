#include "LinuxNativeTCPSocket.h"

#include <thread>
#include <string.h>
#include "Configuration.h"
#include "CustomException.h"

LinuxNativeTCPSocket::LinuxNativeTCPSocket()
{
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketDescriptor == -1) throw CustomException::RuntimeError("Could not create socket");
}

LinuxNativeTCPSocket::LinuxNativeTCPSocket(int socketDescriptor) { this->socketDescriptor = socketDescriptor; }

int LinuxNativeTCPSocket::Descriptor() const { return socketDescriptor; }

void LinuxNativeTCPSocket::Bind(in_port_t portNumber, in_addr_t inputAddress)
{
    sockaddr_in server;

    // не знаю обязательно это или нет
    memset(&server, 0, sizeof(server));

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inputAddress;
    server.sin_port = htons(static_cast<u_int16_t>(portNumber));

    //Bind
    if (bind(socketDescriptor, (struct sockaddr*)&server, sizeof(server)) < 0)
        CustomException::RuntimeErrorCode("Bind failed");
}

void LinuxNativeTCPSocket::ConnectToServer(in_port_t portNumber, in_addr_t serverAddress)
{
    sockaddr_in server;

    // не знаю обязательно это или нет
    memset(&server, 0, sizeof(server));

    server.sin_addr.s_addr = serverAddress;
    server.sin_family = AF_INET;
    server.sin_port = htons(static_cast<u_int16_t>(portNumber));

    //Connect to remote server
    if (connect(socketDescriptor, (struct sockaddr*)&server, sizeof(server)) < 0)
        CustomException::RuntimeErrorCode("Connect failed");
}

void LinuxNativeTCPSocket::Listen() { listen(socketDescriptor, 3); }

void LinuxNativeTCPSocket::WaitConnections(connection_handler connectionHandler)
{
    int newSocketDescriptor, socketSize = sizeof(struct sockaddr_in);
    sockaddr_in client;

    while ((newSocketDescriptor = accept(socketDescriptor, (struct sockaddr*)&client, (socklen_t*)&socketSize)))
    {
        //puts("Connection accepted");
        std::thread([&]() { connectionHandler(newSocketDescriptor); }).detach();
        //if (stop) return;
        //puts("Handler assigned");
    }

    if (newSocketDescriptor < 0) CustomException::RuntimeErrorCode("Accept failed");
}

int LinuxNativeTCPSocket::SendNumber(int num) { return write(socketDescriptor, (void*)&num, sizeof(int)); }

int LinuxNativeTCPSocket::AcceptNumber()
{
    int size, stat;
    do { stat = read(socketDescriptor, &size, sizeof(int)); } while (stat < 0);
    return size;
}

void LinuxNativeTCPSocket::SendMessage(char* message, size_t messageSize)
{
    int stat;
    do { stat = write(socketDescriptor, message, messageSize); } while (stat < 0);
}

ssize_t LinuxNativeTCPSocket::AcceptMessage(char* message, size_t messageSize)
{
    ssize_t stat;

    do { //Read while we get errors that are due to signals.
        stat = read(socketDescriptor, message, messageSize);
    } while (stat < 0);

    return stat;
}

void LinuxNativeTCPSocket::Close()
{
    //stop = true;
    close(socketDescriptor);
}

LinuxNativeTCPSocket::~LinuxNativeTCPSocket() { Close(); }
