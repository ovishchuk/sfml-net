/**
 * @file client.cpp
 * @author Oleksandr Ishchuk (o.v.ishchuk@gmail.com)
 * @version 0.1
 * @date 2023-01-28
 * 
 * @copyright Do what the fuck you want (c) 2023
 * 
 */

#include <SFML/Network.hpp>
#include "commands.hpp"
#include <iostream>

class Client
{
public:
    Client()
    {
        socket.bind(m_port);
        socket.setBlocking(false);
    }
    ~Client()
    {
    }
    void stopServer()
    {
        sf::Packet packet;
        packet << COMMAND_STOP;
        socket.send(packet, server_ip, server_port);
    }
private:
    sf::UdpSocket socket;
    sf::IpAddress m_ip = "127.0.0.1";
    sf::IpAddress server_ip = "127.0.0.1";
    unsigned short m_port = 59301;
    unsigned short server_port = 59300;
};

int main()
{
    Client client;

    std::string command;
    std::cout << "Enter command: ";
    std::cin >> command;

    if ( command == "stop" )
    {
        client.stopServer();
    }

    return 0;
}