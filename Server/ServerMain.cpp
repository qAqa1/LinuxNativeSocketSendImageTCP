#include <iostream>

#include "Configuration.h"
#include "File.h"
#include "LinuxNativeTCPSocket.h"

int SendImage(int socketDescriptor)
{
    LinuxNativeTCPSocket connectionHandler(socketDescriptor);

    std::ifstream file(Configuration::FilePath(), std::ifstream::binary);

    file.seekg(0, file.end);
    int fileSize = file.tellg();
    file.seekg(0, file.beg);

    std::cout << "Total Picture size: " << fileSize << std::endl;

    std::cout << "Sending Picture Size" << std::endl;
    connectionHandler.SendNumber(fileSize);

    //Send Picture as Byte Array
    std::cout << "Sending Picture as Byte Array" << std::endl;

    char readBuffer[256];
    
    std::cout << std::endl << "read_buffer size = " << connectionHandler.AcceptMessage(readBuffer, 255);
    std::cout << std::endl << "read_buffer: \"" << std::string(readBuffer) << "\"" << std::endl;

    File::ForeachByBuffer(file, [&](char* buffer, long long readSize)
        {
            std::cout << "readSize = " << readSize << std::endl;
            connectionHandler.SendMessage(buffer, readSize);
        });
}

int main(int argc, char* argv[])
{
    std::cout << "Server run in directory: " << File::GetExecutableDir() << std::endl;
    //printf("Server run in directory: %s", File::GetExecutableDir().c_str());

    //Create socket
    LinuxNativeTCPSocket server;

    //Bind
    server.Bind(Configuration::Port());

    //Listen
    server.Listen();

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    server.WaitConnections(SendImage);

    //fflush(stdout);
    return 0;
}