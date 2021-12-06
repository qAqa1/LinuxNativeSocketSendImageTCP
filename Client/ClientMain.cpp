#include <iostream>

#include "File.h"
#include "Configuration.h"
#include "LinuxNativeTCPSocket.h"

int receiveImage(LinuxNativeTCPSocket client)
{
    //Get the size of the image
    int size = client.AcceptNumber();

    std::cout << std::endl << "Accepted image size: " << size << std::endl;

    char buffer[] = "Got it";

    // Send verification signal
    // ������ sizeof(long long) ����� ���� �������� 0 ������ � ����� � ��������� ��� ������ strlen, �� � ���� �����
    client.SendMessage(buffer, sizeof(long long));

    puts("Reply sent\n");

    char imageArray[DEFAUL_BUFFER_SIZE_FOR_ITERATING_FILE];
    std::ofstream outfile(Configuration::FilePath(), std::ofstream::binary);
    int receiveSize = 0, readSize, packetIndex = 1;

    while (receiveSize < size)
    {
            readSize = client.AcceptMessage(imageArray, DEFAUL_BUFFER_SIZE_FOR_ITERATING_FILE);
            outfile.write(imageArray, readSize);

            std::cout << "Packet number received: " << packetIndex << std::endl
                      << "Packet size: " << readSize << std::endl;

            //Increment the total number of bytes read
            receiveSize += readSize;
            packetIndex++;

            std::cout << "Total received image size: " << receiveSize << std::endl << std::endl;
    }

    puts("Image successfully Received!");
    return 1;
}

int main(int argc, char* argv[])
{
    std::cout << "Client run in directory: " << File::GetExecutableDir();

    //Create socket
    LinuxNativeTCPSocket client;
    client.ConnectToServer(Configuration::Port(), inet_addr(Configuration::IpAddress().c_str()));

    puts("Connected\n");

    receiveImage(client);
    return 0;
}
