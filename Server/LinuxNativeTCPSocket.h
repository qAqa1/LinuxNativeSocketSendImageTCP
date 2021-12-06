#pragma once

#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <functional>
//#include <atomic>

class LinuxNativeTCPSocket
{
private:
	int socketDescriptor;
	//std::atomic_bool stop = ATOMIC_VAR_INIT(false);
public:
	using connection_handler = std::function<void(int)>;
	LinuxNativeTCPSocket();
	LinuxNativeTCPSocket(int socketDescriptor);
	int Descriptor() const;
	void Bind(in_port_t portNumber, in_addr_t inputAddress = INADDR_ANY);
	void ConnectToServer(in_port_t portNumber, in_addr_t serverAddress);
	void Listen();
	void WaitConnections(connection_handler connectionHandler);
	int SendNumber(int num);
	int AcceptNumber();
	void SendMessage(char* message, size_t messageSize);
	ssize_t AcceptMessage(char* message, size_t messageSize);
	void Close();
	~LinuxNativeTCPSocket();
};
